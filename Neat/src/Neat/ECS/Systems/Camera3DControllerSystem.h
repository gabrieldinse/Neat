#pragma once

#include "Neat/ECS/System.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/Components.h"
#include "Neat/Graphics/Camera.h"
#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class Camera3DControllerSystem
      : public System<Camera3DControllerSystem>
      , public EventListener<Camera3DControllerSystem>
   {
   public:
      Camera3DControllerSystem(float aspectRatio, bool rotationEnabled = true);

      ~Camera3DControllerSystem();

      void init(EventManager& eventManager);

      Camera& getCamera() { return m_camera; }
      const Camera& getCamera() const { return m_camera; }

      void update(EntityManager& entityManager,
         EventManager& eventManager, DeltaTime deltaTime);

      bool listenEvent(const MouseScrolledEvent& event);
      bool listenEvent(const MouseMovedEvent& event);
      bool listenEvent(const WindowResizeEvent& event);

   private:
      Camera m_camera;
      float m_translationSpeed = 0.0f;
      float m_rotationSpeed = 90.0f;
      float m_mouseSensitivity = 0.2f;
      Vector2F m_lastMousePosition;
      bool m_firstMouse = true;
      bool m_rotationEnabled;
   };
}