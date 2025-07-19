#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLGraphicsContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neat {
OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow *window)
    : m_glfwWindow(window) {}

void OpenGLGraphicsContext::init() {
  glfwMakeContextCurrent(m_glfwWindow);

  // Glad initialization (need to be after window creation)
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  NT_CORE_ASSERT(status, "Failed to initialize Glad!");

  NT_CORE_INFO("OpenGL info:");
  NT_CORE_INFO("Vendor: {0}",
               reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
  NT_CORE_INFO("Renderer: {0}",
               reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
  NT_CORE_INFO("Version: {0}",
               reinterpret_cast<const char *>(glGetString(GL_VERSION)));
}

void OpenGLGraphicsContext::onUpdate() { glfwSwapBuffers(m_glfwWindow); }
}  // namespace Neat
