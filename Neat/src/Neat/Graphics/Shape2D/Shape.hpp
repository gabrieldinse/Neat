#pragma once

#include "Neat/Graphics/Renderer2D.hpp"

namespace Neat {
class Shape {
 public:
  virtual ~Shape() = default;

  virtual void draw() const = 0;
};
}  // namespace Neat