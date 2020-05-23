#include "Neat/Renderer/OrthographicCamera.h"
#include "Neat/Core/Log.h"
#include "Neat/Debug/Instrumentator.h"
#include "Neat/Math/Transforms.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Math/Utility.h"


namespace Neat
{
   OrthographicCamera::OrthographicCamera(float left, float right,
      float bottom, float top, float zNear, float zFar)
      : m_projectionMatrix(orthographic(left, right, bottom, top, zNear, zFar))
      , m_viewMatrix(1.0f)
      , m_projectionViewMatrix(m_projectionMatrix * m_viewMatrix)
   {
      NT_PROFILE_FUNCTION();
   }

   void OrthographicCamera::setProjection(float left, float right,
      float bottom, float top, float zNear, float zFar)
   {
      NT_PROFILE_FUNCTION();

      m_projectionMatrix = orthographic(left, right, bottom, top, zNear, zFar);
      m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
   }

   void OrthographicCamera::setPosition(const Vector3& position)
   {
      NT_PROFILE_FUNCTION();

      m_position = position;
      recalculateViewMatrix();
   }

   void OrthographicCamera::setRotation(float rotation)
   {
      NT_PROFILE_FUNCTION();

      m_rotation = rotation;
      recalculateViewMatrix();
   }

   void OrthographicCamera::recalculateViewMatrix()
   {
      NT_PROFILE_FUNCTION();
      Matrix4 transform =
         translate(m_position) * 
         rotate(degreesToRadians(m_rotation), { 0, 0, 1 });

      m_viewMatrix = inverse(transform);
      m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
   }
}