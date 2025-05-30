#pragma once

#include "Neat/ECS/System.hpp"
#include "Neat/Events/Events/MouseScrolledEvent.hpp"
#include "Neat/Events/Events/MouseMovedEvent.hpp"
#include "Neat/Events/Events/WindowResizeEvent.hpp"
#include "Neat/Events/EventManager.hpp"
#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class Camera3DControllerSystem
    : public System<Camera3DControllerSystem>,
      public EventListener<Camera3DControllerSystem> {
 public:
  Camera3DControllerSystem(float aspectRatio, bool rotationEnabled = true);

  ~Camera3DControllerSystem();

  void init(EventManager &eventManager);

  Camera &getCamera() { return m_camera; }
  const Camera &getCamera() const { return m_camera; }

  void update(EntityManager &entityManager, EventManager &eventManager,
              DeltaTime deltaTime);

  bool handleEvent(const MouseScrolledEvent &event);
  bool handleEvent(const MouseMovedEvent &event);
  bool handleEvent(const WindowResizeEvent &event);

 private:
  Camera m_camera;
  float m_translationSpeed = 0.0f;
  float m_rotationSpeed = 90.0f;
  float m_mouseSensitivity = 0.2f;
  Vector2F m_lastMousePosition;
  bool m_firstMouse = true;
  bool m_rotationEnabled;
};
}  // namespace Neat