#ifndef GRAPHICS_ORTHOGRAPHIC_CAMERA_H_
#define GRAPHICS_ORTHOGRAPHIC_CAMERA_H_

#include <cstdint>

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/transformable.h"

class OrthographicCamera : public Transformable {
 public:
  OrthographicCamera(const uint32_t width, const uint32_t height);
  virtual ~OrthographicCamera() = default;

  const glm::vec2 GetViewportSize() const { return viewport_size_; }

  // Transform a point from world to view space
  const glm::vec2 WorldToScreen(const glm::vec2& point) const;

 private:
  glm::vec2 viewport_size_;
};

#endif  // GRAPHICS_ORTHOGRAPHIC_CAMERA_H_
