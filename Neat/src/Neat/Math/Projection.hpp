#pragma once

#include "Neat/Math/Types/TypeMatrixMxN.hpp"

namespace Neat {
template <typename T>
Matrix<4, 4, T> orthographic(const T &left, const T &right, const T &bottom,
                             const T &top, const T &near, const T &far);

template <typename T>
Matrix<4, 4, T> perspective(const T &fov, const T &aspectRatio, const T &near,
                            const T &far);

template <typename T>
Matrix<4, 4, T> lookAtLH(const Vector<3, T> &eye, const Vector<3, T> &target,
                         const Vector<3, T> &upDirection);

template <typename T>
Matrix<4, 4, T> lookAtRH(const Vector<3, T> &eye, const Vector<3, T> &target,
                         const Vector<3, T> &upDirection);
}  // namespace Neat

#include "Neat/Math/Projection.inl"