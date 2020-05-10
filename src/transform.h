#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <ostream>
#include <sstream>
#include <string>

#include "vector2.h"

// XXX: This is not a true transform matrix as SDL is used for rendering and
//      handles rotation, scaling, etc. However, this is implemented ready
//      for when SDL calls are replaced by OpenGL rendering calls.

class Transform {
 public:
  Transform() : Transform(Vector2f(0, 0)) {}
  Transform(const Vector2f& position) : Transform(position, 0.0f, 1.0f) {}
  Transform(const Vector2f& position, const float rotation, const float scale)
      : position_(position), rotation_(rotation), scale_(scale) {}
  ~Transform() = default;

  inline const Vector2f& GetPosition() const { return position_; }
  inline float GetRotation() const { return rotation_; }
  inline float GetScale() const { return scale_; }

  inline void SetPosition(const Vector2f position) { position_ = position; }
  inline void SetRotation(const float rotation) { rotation_ = rotation; }
  inline void SetScale(const float scale) { scale_ = scale; }

  inline void Translate(const Vector2f offset) {
    position_.x += offset.x;
    position_.y += offset.y;
  }

  // Debug

  std::string ToString() const {
    std::stringstream result;
    result << "Transform{"
           << "position: " << position_
           << ", rotation: " << rotation_
           << ", scale: " << scale_
           << "}";
    return result.str();
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const Transform& transform) {
    stream << transform.ToString();
    return stream;
  }

 private:
  Vector2f position_;
  float rotation_;
  float scale_;
};

#endif
