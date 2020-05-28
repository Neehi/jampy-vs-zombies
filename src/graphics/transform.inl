#include "transform.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline Transform::Transform(const glm::vec2& position,
                            const float rotation,
                            const glm::vec2& scale)
    : position_(position), rotation_(rotation), scale_(scale), dirty_(true) {}

inline Transform::Transform(const Transform& other)
    : position_(other.position_),
      rotation_(other.rotation_),
      scale_(other.scale_),
      transform_(other.transform_),
      dirty_(other.dirty_) {}

inline const glm::mat4x4& Transform::GetTransformation() const {
  if (dirty_) {
    // T * R * S
    const glm::mat4x4 translation = glm::translate(
        glm::mat4x4(1.f),
        glm::vec3(position_, 0.f));
    //transform_ = glm::rotate(transform_, rotation_, glm::vec3(0.f, 0.f, 1.f));
    transform_ = glm::scale(translation, glm::vec3(scale_, 1.f));
    dirty_ = false;
  }

  return transform_;
}

inline const glm::vec2& Transform::GetPosition() const {
  return position_;
}

inline float Transform::GetRotation() const {
  return rotation_;
}

inline const glm::vec2& Transform::GetScale() const {
  return scale_;
}

inline void Transform::SetPosition(const glm::vec2& position) {
  position_ = position;
  dirty_ = true;
}

inline void Transform::SetRotation(const float rotation) {
  rotation_ = rotation;
  dirty_ = true;
}

inline void Transform::SetScale(const glm::vec2& scale) {
  scale_ = scale;
  dirty_ = true;
}

inline void Transform::Translate(const glm::vec2& offset) {
  position_ += offset;
  dirty_ = true;
}

inline const glm::vec2 Transform::TransformPoint(const glm::vec2& point) const {
  return GetTransformation() * glm::vec4{point, 0.f, 1.f};
}
