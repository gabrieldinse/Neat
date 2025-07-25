#pragma once

#include <iostream>

#include "Neat/Core/Types.hpp"
#include "Neat/Utils/TypeConversions.hpp"

namespace Neat {
enum class MouseButton : UInt16 {
  Button0 = 0,
  Button1 = 1,
  Button2 = 2,
  Button3 = 3,
  Button4 = 4,
  Button5 = 5,
  Button6 = 6,
  Button7 = 7,
  ButtonLast = Button7,
  ButtonLeft = Button0,
  ButtonRight = Button1,
  ButtonMiddle = Button2
};

inline std::ostream &operator<<(std::ostream &os, MouseButton mouseCode) {
  os << enumToInt(mouseCode);
  return os;
}
}  // namespace Neat
