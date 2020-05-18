#pragma once

#include <utility>

#include "Neat/Core/Core.h"
#include "Neat/Core/KeyCodes.h"
#include "Neat/Core/MouseCodes.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class Input
   {
   public:
      struct InputImpl;

   public:
      static void init(void* window);
      static bool isKeyPressed(KeyCode key);
      static bool isMouseButtonPressed(MouseCode button);
      static Vector2 getMousePosition();
      static float getMouseX();
      static float getMouseY();

   private:
      static std::unique_ptr<InputImpl> s_data;
   };
   
}