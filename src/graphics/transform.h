#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <ostream>
#include <sstream>
#include <string>

#include <glm/vec2.hpp>

// XXX: This is not a true transform matrix as SDL is used for rendering and
//      handles rotation, scaling, etc. However, this is implemented ready
//      for when SDL calls are replaced by OpenGL rendering calls.

class Transform {
 public:
  Transform() : Transform(glm::vec2(0, 0)) {}
  Transform(const glm::vec2& position) : Transform(position, 0.0f, 1.0f) {}
  Transform(const glm::vec2& position, const float rotation, const float scale)
      : position_(position), rotation_(rotation), scale_(scale) {}
  ~Transform() = default;

  inline const glm::vec2& GetPosition() const { return position_; }
  inline float GetRotation() const { return rotation_; }
  inline float GetScale() const { return scale_; }

  inline void SetPosition(const glm::vec2& position) { position_ = position; }
  inline void SetRotation(const float rotation) { rotation_ = rotation; }
  inline void SetScale(const float scale) { scale_ = scale; }

  inline void Translate(const glm::vec2 offset) {
    position_.x += offset.x;
    position_.y += offset.y;
  }

  // Debug

  std::string ToString() const {
    std::stringstream result;
    result << "Transform{"
           << "position: (" << position_.x << ", " << position_.y << ")"
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
  glm::vec2 position_;
  float rotation_;
  float scale_;
};

#endif
