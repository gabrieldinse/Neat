#include "Neat/Core/Application.h"
#include "Neat/Core/Input.h"
#include "Neat/ECS/Systems/Camera2DControllerSystem.h"


namespace Neat
{
   Camera2DControllerSystem::Camera2DControllerSystem(float aspectRatio,
      bool rotationEnabled)
      : m_aspectRatio(aspectRatio)
      , m_position(m_camera.getPosition())
      , m_rotation(m_camera.getRoll())
      , m_rotationEnabled(rotationEnabled)
      , m_lastMousePosition(Input::getMouseX(), Input::getMouseY())
   {
      m_camera.setOrthographic(
         -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
         -m_zoomLevel, m_zoomLevel);
   }

   Camera2DControllerSystem::~Camera2DControllerSystem()
   {
   }

   void Camera2DControllerSystem::init(EventManager& eventManager)
   {
      eventManager.addListener<MouseMovedEvent>(*this);
      eventManager.addListener<MouseScrolledEvent>(*this);
      eventManager.addListener<WindowResizeEvent>(*this);
   }

   void Camera2DControllerSystem::update(
      EntityManager& entityManager, EventManager& eventManager,
      DeltaTime deltaTime)
   {
      if (!((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)) &&
         Input::isMouseButtonPressed(MouseCode::ButtonLeft)))
      {
         if (Input::isKeyPressed(KeyCode::W))
         {
            m_position.y += (float)(m_translationSpeed * deltaTime);
         }

         if (Input::isKeyPressed(KeyCode::S))
         {
            m_position.y -= (float)(m_translationSpeed * deltaTime);
         }

         if (Input::isKeyPressed(KeyCode::D))
         {
            m_position.x += (float)(m_translationSpeed * deltaTime);
         }

         if (Input::isKeyPressed(KeyCode::A))
         {
            m_position.x -= (float)(m_translationSpeed * deltaTime);
         }

         m_camera.setPosition(m_position);
      }

      if (m_rotationEnabled)
      {
         if (Input::isKeyPressed(KeyCode::Q))
         {
            m_rotation += (float)(m_rotationSpeed * deltaTime);
            if (m_rotation >= 360.0f)
               m_rotation -= 360.0f;
            m_camera.setRoll(m_rotation);
         }

         if (Input::isKeyPressed(KeyCode::E))
         {
            m_rotation -= (float)(m_rotationSpeed * deltaTime);
            if (m_rotation <= -360.0f)
               m_rotation += 360.0f;
            m_camera.setRoll(m_rotation);
         }
      }
   }

   bool Camera2DControllerSystem::listenEvent(
      const MouseScrolledEvent& event)
   {
      if ((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)))
      {
         m_zoomLevel -= event.yOffset * 0.2f;
         m_zoomLevel = std::max(m_zoomLevel, 0.25f);
         m_translationSpeed = 2.0f * m_zoomLevel;
         m_camera.setOrthographic(
            -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
            -m_zoomLevel, m_zoomLevel);
      }

      return false;
   }

   bool Camera2DControllerSystem::listenEvent(
      const MouseMovedEvent& event)
   {
      Vector2 current_mouse_position(event.xPos, event.yPos);

      if ((Input::isKeyPressed(KeyCode::LeftControl) ||
         Input::isKeyPressed(KeyCode::RightControl)) &&
         Input::isMouseButtonPressed(MouseCode::ButtonLeft))
      {
         const auto& window = Application::get().getWindow();
         const auto scale_factor =
            2.0f * m_zoomLevel / (float)window.getHeight();

         auto mouse_possition_offset =
            current_mouse_position - m_lastMousePosition;
         auto screen_position_offset =
            rotate(radians(m_rotation), { 0, 0, 1 }) *
            scale(Vector3(-scale_factor, scale_factor, 1.0f)) *
            Vector4(mouse_possition_offset, 0.0f, 1.0f);

         m_position = m_position + Vector3(screen_position_offset);
         m_camera.setPosition(m_position);
      }

      m_lastMousePosition = current_mouse_position;

      return false;
   }

   bool Camera2DControllerSystem::listenEvent(
      const WindowResizeEvent& event)
   {
      m_aspectRatio = (float)event.width / (float)event.height;
      m_camera.setOrthographic(
         -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
         -m_zoomLevel, m_zoomLevel);

      return false;
   }
}