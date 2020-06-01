#include "graphics/orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

OrthographicCamera::OrthographicCamera(const uint32_t width,
                                       const uint32_t height)
    : viewport_size_(width, height) {}

const glm::vec2 OrthographicCamera::WorldToScreen(
    const glm::vec2& point) const {
  return (point - GetTransform().GetPosition())
         * GetTransform().GetScale()
         + viewport_size_ * 0.5f;
}
