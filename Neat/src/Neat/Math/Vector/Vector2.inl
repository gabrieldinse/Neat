#include "Neat/Math/VectorOperations.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   constexpr
   Vec<2, T>::Vec() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   constexpr
   Vec<2, T>::Vec(T scalar) : x(scalar), y(scalar) {}

   template <typename T>
   constexpr
   Vec<2, T>::Vec(T x, T y) : x(x), y(y) {}


   // Copy Constructor
   template <typename T>
   constexpr
   Vec<2, T>::Vec(const Vec<2, T>& v) : x(v.x), y(v.y) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   constexpr
   Vec<2, T>::Vec(const Vec<2, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<2, T>::Vec(const Vec<4, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<2, T>::Vec(const Vec<3, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<2, T>::Vec(const Vec<1, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(0)) {}

   template <typename T>
   template <typename A, typename B>
   constexpr
   Vec<2, T>::Vec(const Vec<1, A>& v, B scalar1)
      : x(static_cast<T>(v.x)), y(static_cast<T>(scalar1)) {}

   template <typename T>
   template <typename X, typename Y>
   constexpr
   Vec<2, T>::Vec(X x, Y y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}


   // Assignment operators
   template <typename T>
   constexpr
   Vec<2, T>& Vec<2, T>::operator=(const Vec<4, T>& other)
   {
      x = other.x;
      y = other.y;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<2, T>& Vec<2, T>::operator=(const Vec<3, T>& other)
   {
      x = other.x;
      y = other.y;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<2, T>& Vec<2, T>::operator=(const Vec<2, T>& other)
   {
      x = other.x;
      y = other.y;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<2, T>& Vec<2, T>::operator=(const Vec<1, T>& other)
   {
      x = other.x;
      y = static_cast<T>(0);

      return *this;
   }


   // Compound assignment operators
   template<typename T>
   template<typename U>
   inline constexpr Vec<2, T>& Vec<2, T>::operator+=(const Vec<2, U>& v)
   {
      x += v.x;
      y += v.y;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<2, T>& Vec<2, T>::operator-=(const Vec<2, U>& v)
   {
      x -= v.x;
      y -= v.y;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<2, T>& Vec<2, T>::operator*=(const Vec<2, U>& v)
   {
      x *= v.x;
      y *= v.y;


      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<2, T>& Vec<2, T>::operator*=(U scalar)
   {
      x *= scalar;
      y *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<2, T>& Vec<2, T>::operator/=(U scalar)
   {
      x /= scalar;
      y /= scalar;

      return *this;
   }


   template <typename T>
   inline constexpr
   Vec<2, T>::operator bool() const
   {
      return (norm(*this) > static_cast<T>(0));
   }
   

   template<typename T>
   inline  constexpr
   T& Vec<2, T>::operator[](std::size_t pos)
   {
      switch (pos)
      {
         case static_cast<T>(0): return x;
         case 1: return y;
      }

      throw VecDimensionError();
   }

   template<typename T>
   inline constexpr
   const T& Vec<2, T>::operator[](std::size_t pos) const
   {
      switch (pos)
      {
         case 0: return x;
         case 1: return y;
      }

      throw VecDimensionError();
   }


   // Non member operators
   template <typename T>
   inline constexpr
      Vec<2, T> operator+(const Vec<2, T>& va, const Vec<2, T>& vb)
   {
      return Vec<2, T>(va) += vb;
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator-(const Vec<2, T>& v)
   {
      return Vec<2, T>(-v.x, -v.y);
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator-(const Vec<2, T>& va, const Vec<2, T>& vb)
   {
      return Vec<2, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator*(const Vec<2, T>& va, const Vec<2, T>& vb)
   {
      return Vec<2, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator*(const Vec<2, T>& va, const Vec<1, T>& vb)
   {
      return Vec<2, T>(va) *= vb.x;
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator*(const Vec<1, T>& va, const Vec<2, T>& vb)
   {
      return Vec<2, T>(vb) *= va.x;
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator*(T scalar, const Vec<2, T>& v)
   {
      return Vec<2, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator*(const Vec<2, T>& v, T scalar)
   {
      return Vec<2, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vec<2, T> operator/(const Vec<2, T>& v, T scalar)
   {
      return Vec<2, T>(v) /= scalar;
   }
}