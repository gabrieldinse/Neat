#include "Neat/Core/Application.h"
#include "Neat/ImGui/ImGuiRender.h"
#include "Neat/Debug/Instrumentator.h"

#include <imgui.h> // need to be before the next two includes
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Neat
{
   void ImGuiRender::init()
   {
      NT_PROFILE_FUNCTION();

      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      auto& io = ImGui::GetIO();
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
      io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
      //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
      //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

      // Setup Dear ImGui style
      ImGui::StyleColorsDark();

      // When viewports are enabled we tweak WindowRounding/WindowBg 
      // so platform windows can look identical to regular ones.
      auto& style = ImGui::GetStyle();
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
         style.WindowRounding = 0.0f;
         style.Colors[ImGuiCol_WindowBg].w = 1.0f;
      }

      auto& application = Application::get();
      auto window = static_cast<GLFWwindow*>(
         application.getWindow().getNativeWindow());

      // Setup Platform/Renderer bindings
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui_ImplOpenGL3_Init("#version 410");
   }

   void ImGuiRender::shutdown()
   {
      NT_PROFILE_FUNCTION();

      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
   }

   void ImGuiRender::begin()
   {
      NT_PROFILE_FUNCTION();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
   }

   void ImGuiRender::end()
   {
      NT_PROFILE_FUNCTION();

      auto& io = ImGui::GetIO();
      auto& app = Application::get();
      io.DisplaySize = ImVec2(
      (float)app.getWindow().getWidth(),
         (float)app.getWindow().getHeight());

      // Rendering
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
         auto backup_current_context = glfwGetCurrentContext();
         ImGui::UpdatePlatformWindows();
         ImGui::RenderPlatformWindowsDefault();
         glfwMakeContextCurrent(backup_current_context);
      }
   }
}