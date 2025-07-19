#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLShaderDataType.hpp"
#include "Platform/OpenGL/OpenGLShaderProgram.hpp"
#include "Neat/Misc/ReadFile.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLShaderProgram::OpenGLShaderProgram(const std::string &filepath)
    : m_id(glCreateProgram()),
      m_name(std::filesystem::path(filepath).stem().string()) {
  build(filepath);
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &name,
                                         const std::string &filepath)
    : m_id(glCreateProgram()), m_name(name) {
  build(filepath);
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &name,
                                         const std::string &vertexSource,
                                         const std::string &fragmentSource)
    : m_id(glCreateProgram()), m_name(name) {
  build(vertexSource, fragmentSource);
}

OpenGLShaderProgram::~OpenGLShaderProgram() { glDeleteProgram(m_id); }

void OpenGLShaderProgram::bind() const { glUseProgram(m_id); }

void OpenGLShaderProgram::unbind() const { glUseProgram(0); }

void OpenGLShaderProgram::set(const std::string &name, float value) {
  glUniform1f(getUniformLocation(name), value);
}

void OpenGLShaderProgram::set(const std::string &name, Vector2F values) {
  glUniform2f(getUniformLocation(name), values.x, values.y);
}

void OpenGLShaderProgram::set(const std::string &name, Vector3F values) {
  glUniform3f(getUniformLocation(name), values.x, values.y, values.z);
}

void OpenGLShaderProgram::set(const std::string &name, Vector4F values) {
  glUniform4f(getUniformLocation(name), values.x, values.y, values.z, values.w);
}

void OpenGLShaderProgram::set(const std::string &name, Int32 value) {
  glUniform1i(getUniformLocation(name), value);
}

void OpenGLShaderProgram::set(const std::string &name, Int32 *values,
                              UInt32 count) {
  glUniform1iv(getUniformLocation(name), count, values);
}

void OpenGLShaderProgram::set(const std::string &name, Matrix3F matrix) {
  glUniformMatrix3fv(getUniformLocation(name), 1, GL_TRUE,
                     matrix.dataPointer());
}

void OpenGLShaderProgram::set(const std::string &name, Matrix4F matrix) {
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE,
                     matrix.dataPointer());
}

Int32 OpenGLShaderProgram::getUniformLocation(const std::string &name) {
  if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
    return m_uniformLocationCache[name];
  }

  auto location = glGetUniformLocation(m_id, name.c_str());
  NT_CORE_ASSERT(location != -1, "Uniform does not exist.");

  m_uniformLocationCache[name] = location;
  return location;
}

void OpenGLShaderProgram::build(const std::string &filepath) {
  readFile(filepath)
      .transform([this](const std::string &shaderSources) {
        const auto &[vertex_source, fragment_source] =
            splitShaderSources(shaderSources);
        build(vertex_source, fragment_source);
      })
      .or_else([](const FileError &error) {
        NT_CORE_ERROR("Failed to read shader file: {0}", error);
      });
}

void OpenGLShaderProgram::build(const std::string &vertexSource,
                                const std::string &fragmentSource) {
  UInt32 vertex_shader_id = compileShader(GL_VERTEX_SHADER, vertexSource);
  UInt32 fragment_shader_id = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
  linkShaders(vertex_shader_id, fragment_shader_id);
}

std::pair<std::string, std::string> OpenGLShaderProgram::splitShaderSources(
    const std::string &shaderSources) {
  constexpr const char *type_token = "#type";
  auto type_token_length = strlen(type_token);
  auto pos = shaderSources.find(type_token, 0);
  std::string vertex_source, fragment_source;

  while (pos != std::string::npos) {
    auto shader_type_begin =
        shaderSources.find_first_not_of(" \t", pos + type_token_length);
    auto shader_type_end =
        shaderSources.find_first_of(" \t\r\n", shader_type_begin);
    auto eol_pos = shaderSources.find_first_of("\r\n", shader_type_end);

    NT_CORE_ASSERT(eol_pos != std::string::npos,
                   "OpenGLShaderProgram source syntax error.");

    auto shader_type_name = shaderSources.substr(
        shader_type_begin, shader_type_end - shader_type_begin);
    auto shader_type = OpenGLTypeConverter::getShaderDataType(shader_type_name);

    auto next_line_pos = shaderSources.find_first_not_of("\r\n", eol_pos);
    pos = shaderSources.find(type_token, next_line_pos);
    std::string shader_source = shaderSources.substr(
        next_line_pos, (pos == std::string::npos ? pos : pos - next_line_pos));

    switch (shader_type) {
      case GL_VERTEX_SHADER:
        vertex_source = shader_source;
        break;
      case GL_FRAGMENT_SHADER:
        fragment_source = shader_source;
        break;
      default:
        NT_CORE_ASSERT(false, "Unknown shader type.");
    }
  }

  return {vertex_source, fragment_source};
}

UInt32 OpenGLShaderProgram::compileShader(UInt32 type,
                                          const std::string &shaderSource) {
  UInt32 shader_id = glCreateShader(type);

  const char *c_str_source = shaderSource.c_str();
  glShaderSource(shader_id, 1, &c_str_source, 0);
  glCompileShader(shader_id);

  Int32 compiled = 0;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
  if (compiled == GL_FALSE) {
    Int32 max_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<char> info_log(max_length);
    glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);

    glDeleteShader(shader_id);

    NT_CORE_ERROR("OpenGLShaderProgram compilation failure\n{0}",
                  info_log.data());
    NT_CORE_ASSERT(false, "");
  }

  glAttachShader(m_id, shader_id);
  return shader_id;
}

void OpenGLShaderProgram::linkShaders(UInt32 vertexShaderId,
                                      UInt32 fragmentShaderId) {
  glLinkProgram(m_id);

  Int32 linked = 0;
  glGetProgramiv(m_id, GL_LINK_STATUS, static_cast<Int32 *>(&linked));
  if (linked == GL_FALSE) {
    Int32 max_length = 0;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<char> info_log(max_length);
    glGetProgramInfoLog(m_id, max_length, &max_length, &info_log[0]);

    glDeleteProgram(m_id);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    NT_CORE_ERROR("OpenGLShaderProgram link failure\n{0}", info_log.data());
    NT_CORE_ASSERT(false, "");
  }

  glDetachShader(m_id, vertexShaderId);
  glDetachShader(m_id, fragmentShaderId);
}
}  // namespace Neat