#include <cmath>
#include <algorithm>

#include "Neat/Math/Types/TypeVectorN.h"
#include "Neat/Math/Types/FunctorVector.h"
#include "Neat/Math/Types/FunctorDoubleVector.h"
#include "Neat/Math/Types/FunctorTripleVector.h"


namespace Neat
{
   template<typename T>
   T min(T a, T b)
   {
      return std::min(a, b);
   }

   template<UInt32 N, typename T>
   Vector<N, T> min(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return FunctorDoubleVector<Vector, N, T, T>::call(min, va, vb);
   }

   template<typename T>
   T max(T a, T b)
   {
      return std::max(a, b);
   }

   template<UInt32 N, typename T>
   Vector<N, T> max(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return FunctorDoubleVector<Vector, N, T, T>::call(max, va, vb);
   }

   template<typename T>
   T abs(T value)
   {
      return std::abs(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> abs(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(abs, v);
   }

   template<typename T>
   T round(T value)
   {
      return std::round(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> round(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(round, v);
   }

   template<typename T>
   T trunc(T value)
   {
      return std::trunc(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> trunc(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(trunc, v);
   }

   template<typename T>
   T fract(T value)
   {
      return std::fract(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> fract(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(fract, v);
   }

   template<typename T>
   T mod(T a, T b)
   {
      return a - b * floor(a / b);
   }

   template<UInt32 N, typename T>
   Vector<N, T> mod(const Vector<N, T>& v, T value)
   {
      return FunctorDoubleVector<Vector, N, T, T>::call(
         mod, v, Vector<N, T>(value));
   }

   template<UInt32 N, typename T>
   Vector<N, T> mod(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return FunctorDoubleVector<Vector, N, T, T>::call(mod, va, vb);
   }

   template<typename T>
   T clamp(T value, T low, T high)
   {
      return std::clamp(value, low, high);
   }

   template<UInt32 N, typename T>
   Vector<N, T> clamp(const Vector<N, T>& v, T low, T high)
   {
      return FunctorTripleVector<Vector, N, T, T>::call(
         clamp, v, Vector<N, T>(low), Vector<N, T>(high));
   }

   template<UInt32 N, typename T>
   Vector<N, T> clamp(const Vector<N, T>& v, const Vector<N, T>& low,
      const Vector<N, T>& high)
   {
      return FunctorTripleVector<Vector, N, T, T>::call(clamp, v, low, high);
   }

   template<typename T>
   T floor(T value)
   {
      return std::floor(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> floor(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(floor, v);
   }

   template<typename T>
   T ceil(T value)
   {
      return std::ceil(value);
   }

   template<UInt32 N, typename T>
   Vector<N, T> ceil(const Vector<N, T>& v)
   {
      return FunctorVector<Vector, N, T, T>::call(ceil, v);
   }
}