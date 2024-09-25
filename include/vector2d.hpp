#pragma once

#include <cmath>
#include <iostream>
template <typename T> class Vector2D {
public:
  // Data members
  T x, y;

  // Constructors
  Vector2D() : x(NULL), y(NULL) {}   // Default constructor
  Vector2D(T x, T y) : x(x), y(y) {} // Parameterized constructor

  // Operator Overloads
  // Unary plus and minus
  Vector2D<T> operator+() const { return *this; }

  Vector2D<T> operator-() const { return Vector2D(-x, -y); }

  // Addition
  Vector2D<T> operator+(const Vector2D<T> &other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  Vector2D<T> &operator+=(const Vector2D<T> &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  // Subtraction
  Vector2D<T> operator-(const Vector2D<T> &other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  Vector2D<T> &operator-=(const Vector2D<T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  // Scalar multiplication
  Vector2D operator*(T scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }

  Vector2D &operator*=(T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  // Scalar division
  Vector2D operator/(double scalar) const {
    return Vector2D(x / scalar, y / scalar);
  }

  Vector2D &operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  template <typename U = T>
  typename std::enable_if<std::is_floating_point<U>::value, Vector2D<U>>::type
  operator/(U scalar) const {
    return Vector2D(x / scalar, y / scalar);
  }

  template <typename U = T>
  typename std::enable_if<std::is_floating_point<U>::value, Vector2D<U> &>::type
  operator/=(U scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  // Equality comparison
  bool operator==(const Vector2D<T> &other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Vector2D<T> &other) const { return !(*this == other); }

  // Dot product
  T dot(const Vector2D<T> &other) const { return x * other.x + y * other.y; }

  // Magnitude (Length)
  template <typename U = T>
  typename std::enable_if<std::is_floating_point<U>::value, U>::type
  magnitude() const {
    return std::sqrt(x * x + y * y);
  }

  // Normalize the vector (only for floating point types)
  template <typename U = T>
  typename std::enable_if<std::is_floating_point<U>::value, Vector2D<U>>::type
  normalize() const {
    U mag = magnitude();
    return Vector2D(x / mag, y / mag);
  }

  // Stream insertion (for output)
  friend std::ostream &operator<<(std::ostream &os, const Vector2D &v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
  }

  // Stream extraction (for input)
  friend std::istream &operator>>(std::istream &is, Vector2D &v) {
    is >> v.x >> v.y;
    return is;
  }
};
