#pragma once

#include "Neat/Core/Core.h"
#include "Neat/Core/Window.h"
#include "Neat/Core/LayerGroup.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Events/Event.h"


namespace Neat
{
   class Application : public EventSubscriber<Application>
   {
   public:
      Application();
      virtual ~Application();

      void run();
      void stop();
      virtual void update(DeltaTime deltaTime) {}

      template <typename T, typename... Args>
      void pushLayer(Args&&... args);
      template <typename T, typename... Args>
      void pushOverlay(Args&&... args);
      void pushLayer(std::unique_ptr<Layer>&& layer);
      void pushOverlay(std::unique_ptr<Layer>&& layer);
      std::unique_ptr<Layer> popLayer(Int position);
      std::unique_ptr<Layer> popOverlay(Int position);

      void setUpdateRate(double rate) { m_updatePeriod = 1.0f / rate; }

      static Application& get() { return *s_instance; }
      Window& getWindow() { return *m_window; }

      // Events receiving
      bool receive(const WindowCloseEvent& event);
      bool receive(const WindowResizeEvent& event);

      EventManager& events() { return m_events; }

      virtual void imGuiRender() {}

   private:
      static Application* s_instance;

      std::unique_ptr<Window> m_window;
      EventManager m_events;
      LayerGroup m_layerGroup;
      double m_updatePeriod = 1.0f / 120.0f;

      bool m_running = false;
   };

   std::unique_ptr<Application> createApplication();


   template <typename T, typename... Args>
   void Application::pushLayer(Args&&... args)
   {
      m_layerGroup.pushLayer<T>(std::forward<Args>(args)...);
   }

   template <typename T, typename... Args>
   void Application::pushOverlay(Args&&... args)
   {
      m_layerGroup.pushOverlay<T>(std::forward<Args>(args)...);
   }
}


