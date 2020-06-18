#pragma once

#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   template <typename T>
   struct Vector<4, T>
   {
      using Type = Vector<4, T>;
      using ValueType = T;


      // Class Data
      union
      {
         struct { T x, y, z, w; };
         struct { T r, g, b, a; };
         struct { T i, j, k, l; };
         struct { T s, t, p, q; };
      };


      // Default constructor
      constexpr Vector();


      // Basic Constructors
      constexpr explicit Vector(const T& scalar);

      constexpr Vector(const T& x, const T& y, const T& z, const T& w);


      // Copy Constructor
      constexpr Vector(const Vector<4, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit Vector(const Vector<4, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<3, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<2, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<1, U>& v);
      template <typename A, typename B>
      constexpr explicit Vector(const Vector<3, A>& v, const B& scalar);

      template <typename A, typename B, typename C>
      constexpr explicit Vector(const Vector<2, A>& v, const B& scalar1,
         const C& scalar2);

      template <typename A, typename B, typename C, typename D>
      constexpr explicit Vector(const Vector<1, A>& v, const B& scalar1,
         const C& scalar2, const D& scalar3);

      template <typename X, typename Y, typename Z, typename W>
      constexpr Vector(const X& x, const Y& y, const Z& z, const W& w);

      constexpr Vector(const T* data, UInt32 count);

      // Assignment operators
      constexpr Vector<4, T>& operator=(const Vector<4, T>& other) = default;
      template <typename U>
      constexpr Vector<4, T>& operator=(const Vector<4, U>& other);

      // Compound assignment operators
      template <typename U>
      constexpr Vector<4, T>& operator+=(const Vector<4, U>& v);
      template <typename U>
      constexpr Vector<4, T>& operator-=(const Vector<4, U>& v);
      template <typename U>
      constexpr Vector<4, T>& operator*=(const Vector<4, U>& v);
      template <typename U>
      constexpr Vector<4, T>& operator*=(const Vector<1, U>& v);
      template <typename U>
      constexpr Vector<4, T>& operator*=(const U& scalar);
      template <typename U>
      constexpr Vector<4, T>& operator/=(const U& scalar);

      // Explicit conversion operators
      constexpr explicit operator bool() const;

      // Element acessing
      constexpr T& operator[](UInt32 pos);
      constexpr const T& operator[](UInt32 pos) const;
      constexpr T& operator()(UInt32 pos) { return (*this)[pos]; }
      constexpr const T& operator()(UInt32 pos) const { return (*this)[pos]; }
      constexpr T* dataPointer() { return &x; }
      constexpr const T* dataPointer() const { return &x; }

      // Static member variables
      static constexpr UInt32 size() { return 4; }
      static constexpr UInt32 length() { return size(); }
   };


   // Predefined types
   using Vector4 = Vector<4, float>;
   using IVector4 = Vector<4, Int32>;
   using UIVector4 = Vector<4, UInt32>;
   using BVector4 = Vector<4, bool>;
   using DVector4 = Vector<4, double>;


   // Nom member operators
   template <typename T>
   inline constexpr Vector<4, T> operator+(const Vector<4, T>& va,
      const Vector<4, T>& vb);

   template <typename T>
   inline constexpr Vector<4, T> operator-(const Vector<4, T>& v);

   template <typename T>
   inline constexpr Vector<4, T> operator-(const Vector<4, T>& va,
      const Vector<4, T>& vb);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Vector<4, T>& va,
      const Vector<4, T>& vb);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Vector<4, T>& va,
      const Vector<1, T>& vb);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Vector<1, T>& va,
      const Vector<4, T>& vb);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const T& scalar,
      const Vector<4, T>& v);

   template <typename T>
   inline constexpr Vector<4, T> operator*(const Vector<4, T>& v,
      const T& scalar);

   template <typename T>
   inline constexpr Vector<4, T> operator/(const Vector<4, T>& v,
      const T& scalar);


   // Relational operators
   template <typename T>
   inline constexpr bool operator==(const Vector<4, T>& va,
      const Vector<4, T>& vb);

   template <typename T>
   inline constexpr bool operator!=(const Vector<4, T>& va,
      const Vector<4, T>& vb);


   // Vector operations
   template <typename T>
   inline T dot(const Vector<4, T>& va, const Vector<4, T>& vb);

   template <typename T>
   inline T norm(const Vector<4, T>& v);

   template <typename T>
   inline Vector<4, T> normalize(const Vector<4, T>& v);
}

#include "Neat/Math/Types/Vector4.inl"