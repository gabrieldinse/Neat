#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"
#include "Platform/OpenGL/OpenGLShaderProgramBuilder.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class OpenGLShaderProgram : public ShaderProgram {
 public:
  OpenGLShaderProgram(const std::string &filepath);
  OpenGLShaderProgram(const std::string &name, const std::string &filepath);
  OpenGLShaderProgram(const std::string &name, const std::string &vertexSource,
                      const std::string &fragmentSource);
  virtual ~OpenGLShaderProgram();

  virtual void use() const override;
  virtual void unuse() const override;

  virtual const std::string &getName() const override { return m_name; }
  virtual void setName(const std::string &name) override { m_name = name; }
  virtual void set(const std::string &name, float value) override;
  virtual void set(const std::string &name, Vector2F values) override;
  virtual void set(const std::string &name, Vector3F values) override;
  virtual void set(const std::string &name, Vector4F values) override;
  virtual void set(const std::string &name, Int32 value) override;
  virtual void set(const std::string &name, Int32 *values,
                   UInt32 count) override;
  virtual void set(const std::string &name, Matrix3F matrix) override;
  virtual void set(const std::string &name, Matrix4F matrix) override;

 private:
  Int32 getUniformLocation(const std::string &name);

 private:
  UInt32 m_id = 0;
  std::unordered_map<std::string, Int32> m_uniformLocationCache;
  std::string m_name;
};
}  // namespace Neat