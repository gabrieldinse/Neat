#include "Neat/Math/VectorOperations.h"
#include "Vector4.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   constexpr
   Vec<4, T>::Vec()
      : x(static_cast<T>(0))
      , y(static_cast<T>(0))
      , z(static_cast<T>(0))
      , w(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   constexpr
   Vec<4, T>::Vec(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

   template <typename T>
   constexpr
   Vec<4, T>::Vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}


   // Copy Constructor
   template <typename T>
   constexpr
   Vec<4, T>::Vec(const Vec<4, T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   constexpr
   Vec<4, T>::Vec(const Vec<4, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z))
      , w(static_cast<T>(v.w)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<4, T>::Vec(const Vec<3, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z))
      , w(static_cast<T>(0)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<4, T>::Vec(const Vec<2, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(0))
      , w(static_cast<T>(0)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<4, T>::Vec(const Vec<1, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(0))
      , z(static_cast<T>(0))
      , w(static_cast<T>(0)) {}

   template <typename T>
   template <typename A, typename B>
   constexpr
   Vec<4, T>::Vec(const Vec<3, A>& v, B scalar)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z))
      , w(static_cast<T>(scalar)) {}

   template <typename T>
   template <typename A, typename B, typename C>
   constexpr
   Vec<4, T>::Vec(const Vec<2, A>& v, B scalar1, C scalar2)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(scalar1))
      , w(static_cast<T>(scalar2)) {}

   template <typename T>
   template <typename A, typename B, typename C, typename D>
   constexpr
   Vec<4, T>::Vec(const Vec<1, A>& v, B scalar1, C scalar2, D scalar3)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(scalar1))
      , z(static_cast<T>(scalar2))
      , w(static_cast<T>(scalar3)) {}

   template <typename T>
   template <typename X, typename Y, typename Z, typename W>
   constexpr
   Vec<4, T>::Vec(X x, Y y, Z z, W w)
      : x(static_cast<T>(x))
      , y(static_cast<T>(y))
      , z(static_cast<T>(z))
      , w(static_cast<T>(w)) {}


   // Assignment operators
   template <typename T>
   constexpr
   Vec<4, T>& Vec<4, T>::operator=(const Vec<4, T>& other)
   {
      this->x = other.x;
      this->y = other.y;
      this->z = other.z;
      this->w = other.w;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<4, T>& Vec<4, T>::operator=(const Vec<3, T>& other)
   {
      this->x = other.x;
      this->y = other.y;
      this->z = other.z;
      this->w = static_cast<T>(0);

      return *this;
   }

   template <typename T>
   constexpr
   Vec<4, T>& Vec<4, T>::operator=(const Vec<2, T>& other)
   {
      this->x = other.x;
      this->y = other.y;
      this->z = static_cast<T>(0);
      this->w = static_cast<T>(0);

      return *this;
   }

   template <typename T>
   constexpr
   Vec<4, T>& Vec<4, T>::operator=(const Vec<1, T>& other)
   {
      this->x = other.x;
      this->y = static_cast<T>(0);
      this->z = static_cast<T>(0);
      this->w = static_cast<T>(0);

      return *this;
   }


   // Compound assigment operators
   template<typename T>
   template<typename U>
   inline constexpr
   Vec<4, T>& Vec<4, T>::operator+=(const Vec<4, U>& v)
   {
      this->x += v.x;
      this->y += v.y;
      this->z += v.z;
      this->w += v.w;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vec<4, T>& Vec<4, T>::operator-=(const Vec<4, U>& v)
   {
      this->x -= v.x;
      this->y -= v.y;
      this->z -= v.z;
      this->w -= v.w;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vec<4, T>& Vec<4, T>::operator*=(const Vec<4, U>& v)
   {
      this->x *= v.x;
      this->y *= v.y;
      this->z *= v.z;
      this->w *= v.w;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vec<4, T>& Vec<4, T>::operator*=(U scalar)
   {
      this->x *= scalar;
      this->y *= scalar;
      this->z *= scalar;
      this->w *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vec<4, T>& Vec<4, T>::operator/=(U scalar)
   {
      this->x /= static_cast<T>(scalar);
      this->y /= static_cast<T>(scalar);
      this->z /= static_cast<T>(scalar);
      this->w /= static_cast<T>(scalar);

      return *this;
   }


   template <typename T>
   inline constexpr
   Vec<4, T>::operator Bool() const
   {
      return (norm(*this) > static_cast<T>(0));
   }


   template<typename T>
   inline constexpr
   T& Vec<4, T>::operator[](SizeType pos)
   {
      switch (pos)
      {
         case 0: return this->x;
         case 1: return this->y;
         case 2: return this->z;
         case 3: return this->w;
      }

      throw VecDimensionError("Wrong Vec dimension being acessed!");
   }

   template<typename T>
   inline constexpr
   const T& Vec<4, T>::operator[](SizeType pos) const
   {
      switch (pos)
      {
         case 0: return this->x;
         case 1: return this->y;
         case 2: return this->z;
         case 3: return this->w;
      }

      throw VecDimensionError("Wrong Vec dimension being acessed!");
   }


   // Non member operators
   template <typename T>
   inline constexpr
   Vec<4, T> operator+(const Vec<4, T>& va, const Vec<4, T>& vb)
   {
      return Vec<4, T>(va) += vb;
   }

   template <typename T>
   inline constexpr
   Vec<4, T> operator-(const Vec<4, T>& v)
   {
      return Vec<4, T>(-v.x, -v.y, -v.z, -v.w);
   }

   template <typename T>
   inline constexpr
   Vec<4, T> operator-(const Vec<4, T>& va, const Vec<4, T>& vb)
   {
      return Vec<4, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Vec<4, T>& va, const Vec<4, T>& vb)
   {
      return Vec<4, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Vec<4, T>& va, const Vec<1, T>& vb)
   {
      return Vec<4, T>(va) *= vb.x;
   }

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Vec<1, T>& va, const Vec<4, T>& vb)
   {
      return Vec<4, T>(vb) *= va.x;
   }

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(T scalar, const Vec<4, T>& v)
   {
      return Vec<4, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vec<4, T> operator*(const Vec<4, T>& v, T scalar)
   {
      return Vec<4, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vec<4, T> operator/(const Vec<4, T>& v, T scalar)
   {
      return Vec<4, T>(v) /= scalar;
   }
}