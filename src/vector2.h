#pragma once
#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>
#include <sstream>
#include <string>

template <typename T>
class Vector2 {
 public:
  T x;
  T y;

 public:
  Vector2() : Vector2(0, 0) {}
  Vector2(T x, T y) : x(x), y(y) {}

  // Addition

  inline Vector2<T>& operator+=(const Vector2<T>& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Vector2<T>& operator+=(const T scalar) {
    x += scalar;
    y += scalar;
    return *this;
  }

  friend Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs) {
    lhs += rhs;
    return lhs;
  }

  friend Vector2<T> operator+(Vector2<T> lhs, const T scalar) {
    lhs += scalar;
    return lhs;
  }

  // Subtraction

  inline Vector2<T>& operator-=(const Vector2<T>& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  inline Vector2<T>& operator-=(const T scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
  }

  friend Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs) {
    lhs -= rhs;
    return lhs;
  }

  friend Vector2<T> operator-(Vector2<T> lhs, const T scalar) {
    lhs -= scalar;
    return lhs;
  }

  // Mutliplication

  inline Vector2<T>& operator*=(const Vector2<T>& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  inline Vector2<T>& operator*=(const T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  friend Vector2<T> operator*(Vector2<T> lhs, const Vector2<T>& rhs) {
    lhs *= rhs;
    return lhs;
  }

  friend Vector2<T> operator*(Vector2<T> lhs, const T scalar) {
    lhs *= scalar;
    return lhs;
  }

  // Division

  inline Vector2<T>& operator/=(const Vector2<T>& rhs) {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  inline Vector2<T>& operator/=(const T scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  friend Vector2<T> operator/(Vector2<T> lhs, const Vector2<T>& rhs) {
    lhs /= rhs;
    return lhs;
  }

  friend Vector2<T> operator/(Vector2<T> lhs, const T scalar) {
    lhs /= scalar;
    return lhs;
  }

  // Comparison

  bool operator==(const Vector2<T>& rhs) const {
    return x == rhs.x && y == rhs.y;
  }

  bool operator!=(const Vector2<T>& rhs) const {
    return !(*this == rhs); 
  }

  // Debug

  std::string ToString() const {
    std::stringstream result;
    result << "Vector2(" << x << ", " << y << ")";
    return result.str();
  }

  friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector) {
    stream << vector.ToString();
    return stream;
  }
};

typedef Vector2<float> Vector2f;

#endif
