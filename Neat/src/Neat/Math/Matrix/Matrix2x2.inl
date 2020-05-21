#pragma once


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix() : m_flattened{} {}


   // Basic constructors
   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix(
      T m00, T m01,
      T m10, T m11)
      : m_rows{
         RowType(m00, m01),
         RowType(m10, m11)
         } {}

   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix(T scalar)
      : m_rows{
         RowType(scalar, 0),
         RowType(0, scalar)
         } {}

   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<2, 2, T>& m)
      : m_rows{m[0], m[1]} {}


   // Conversion constructors
   template <typename T>
   template <
      typename X1, typename Y1,
      typename X2, typename Y2>
   inline constexpr
   Matrix<2, 2, T>::Matrix(
      X1 m00, Y1 m01,
      X2 m10, Y2 m11)
      : m_rows{
         RowType(m00, m01),
         RowType(m10, m11)
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<2, 2, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<4, 4, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<3, 3, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1])
         } {}

   template<typename T>
   template<typename V1, typename V2>
   inline constexpr
   Matrix<2, 2, T>::Matrix(
      const Vector<2, V1> row1,
      const Vector<2, V2> row2)
      : m_rows{
         RowType(row1),
         RowType(row2)
         } {}


   // Non member operators
   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator+(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0] + mb[0],
         ma[1] + mb[1]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator-(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0] - mb[0],
         ma[1] - mb[1]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0][0] * mb[0][0] + ma[0][1] * mb[1][0],
         ma[0][0] * mb[0][1] + ma[0][1] * mb[1][1],
         ma[1][0] * mb[0][0] + ma[1][1] * mb[1][0],
         ma[1][0] * mb[0][1] + ma[1][1] * mb[1][1],
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(T scalar, const Matrix<2, 2, T>& m)
   {
      return Matrix<2, 2, T>(
         scalar * m[0],
         scalar * m[1]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(const Matrix<2, 2, T>& m, T scalar)
   {
      return scalar * m;
   }

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const Matrix<2, 2, T>& m, const Vector<2, T>& v)
   {
      return Vector<2, T>(
         m[0][0] * v[0] + m[0][1] * v[1],
         m[1][0] * v[0] + m[1][1] * v[1]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator/(const Matrix<2, 2, T>& m, T scalar)
   {
      return Matrix<2, 2, T>(
         m[0] / scalar,
         m[1] / scalar
         );
   }


   // Assignment operators
   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<2, 2, T>& Matrix<2, 2, T>::operator=(const Matrix<2, 2, U>& m)
   {
      m_rows[0] = m[0];
      m_rows[1] = m[1];

      return *this
   }


   // Compound assigment operators
   template<typename T>
	template<typename U>
   inline constexpr
   Matrix<2, 2, T>& Matrix<2, 2, T>::operator+=(Matrix<2, 2, U> const& m)
	{
		m_rows[0] += m[0];
		m_rows[1] += m[1];

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<2, 2, T>& Matrix<2, 2, T>::operator-=(U scalar)
	{
		m_rows[0] -= scalar;
		m_rows[1] -= scalar;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<2, 2, T>& Matrix<2, 2, T>::operator-=(Matrix<2, 2, U> const& m)
	{
		m_rows[0] -= m[0];
		m_rows[1] -= m[1];

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<2, 2, T>& Matrix<2, 2, T>::operator*=(U scalar)
	{
		m_rows[0] *= scalar;
		m_rows[1] *= scalar;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<2, 2, T>& Matrix<2, 2, T>::operator*=(Matrix<2, 2, U> const& m)
	{
		return (*this = *this * m);
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<2, 2, T>& Matrix<2, 2, T>::operator/=(U scalar)
	{
		m_rows[0] /= scalar;
		m_rows[1] /= scalar;

		return *this;
	}


   // Element accessing
   template <typename T>
   inline constexpr
   typename Matrix<2, 2, T>::RowType& Matrix<2, 2, T>::operator[](std::size_t row)
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   const typename Matrix<2, 2, T>::RowType& Matrix<2, 2, T>::operator[](
      std::size_t row) const
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   T& Matrix<2, 2, T>::operator()(std::size_t pos)
   {
      return m_flattened[pos];
   }

   template <typename T>
   inline constexpr
   const T& Matrix<2, 2, T>::operator()(std::size_t pos) const
   {
      return m_flattened[pos];
   }
}