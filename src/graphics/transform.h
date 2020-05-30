#ifndef GRAPHICS_TRANSFORM_H_
#define GRAPHICS_TRANSFORM_H_

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

class Transform {
 public:
  // -- Constructors --

  Transform() = default;
  Transform(const glm::vec2& position,
            const float rotation,
            const glm::vec2& scale);
  Transform(const Transform& other);
  ~Transform() = default;

  // -- Accessors --

  // Get the transformation matrix for the combined position, rotation and
  // scale transforms to transform a point from local to world space
  const glm::mat4x4& GetTransformation() const;  // XXX: Rename?

  const glm::vec2& GetPosition() const;
  float GetRotation() const;
  const glm::vec2& GetScale() const;

  // -- Modifiers --

  void SetPosition(const glm::vec2& position);
  void SetRotation(const float rotation);
  void SetScale(const glm::vec2& scale);

  void Translate(const glm::vec2& offset);

  // -- Conversions --

  // Transform a point from local to world space
  const glm::vec2 TransformPoint(const glm::vec2& point) const;

 private:
  glm::vec2 position_{0.f, 0.f};
  float rotation_{0.f};
  glm::vec2 scale_{1.f, 1.f};

  // The transformation matrix
  mutable glm::mat4x4 transform_{1.f};
  mutable bool dirty_{true};  // Matrix needs updating?
};

#include "transform.inl"

#endif  // GRAPHICS_TRANSFORM_H_
