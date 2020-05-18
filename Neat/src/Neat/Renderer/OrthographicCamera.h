#pragma once

#include "Neat/Math/Matrix.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class OrthographicCamera
   {
   public:
      OrthographicCamera(float left, float right, float bottom, float top);
      void setProjection(float left, float right, float bottom, float top);
      
      const Vector3& getPosition() const { return m_position; }
      float getRotation() const { return m_rotation; }
      void setPosition(const Vector3& position);
      void setRotation(float rotation);

      const Matrix4& getProjectionMatrix() const { return m_projectionMatrix; }
      const Matrix4& getViewMatrix() const { return m_viewMatrix; }
      const Matrix4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

   private:
      void recalculateViewMatrix();

   private:
      Matrix4 m_projectionMatrix;
      Matrix4 m_viewMatrix;
      Matrix4 m_viewProjectionMatrix;
      Vector3 m_position = {0.0f, 0.0f, 0.0f};
      float m_rotation = 0.0f;
   };
}