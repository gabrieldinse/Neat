#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Math/Vector/Vector1.h"
#include "Neat/Math/Vector/Vector2.h"
#include "Neat/Math/Vector/Vector3.h"
#include "Neat/Math/Vector/Vector4.h"


namespace Neat
{
   // Predefined Vector names
   using Vector1     = Vector<1, float>;
   using Vector2     = Vector<2, float>;
   using Vector3     = Vector<3, float>;
   using Vector4     = Vector<4, float>;
                    
   using IVector1    = Vector<1, Int>;
   using IVector2    = Vector<2, Int>;
   using IVector3    = Vector<3, Int>;
   using IVector4    = Vector<4, Int>;

   using UIVector1   = Vector<1, UInt>;
   using UIVector2   = Vector<2, UInt>;
   using UIVector3   = Vector<3, UInt>;
   using UIVector4   = Vector<4, UInt>;
                    
   using BVector1    = Vector<1, bool>;
   using BVector2    = Vector<2, bool>;
   using BVector3    = Vector<3, bool>;
   using BVector4    = Vector<4, bool>;
                     
   using DVector1    = Vector<1, double>;
   using DVector2    = Vector<2, double>;
   using DVector3    = Vector<3, double>;
   using DVector4    = Vector<4, double>;
}

