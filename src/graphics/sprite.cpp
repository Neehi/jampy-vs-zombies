#include "graphics/sprite.h"

void Sprite::Render(const Renderer& renderer) const {
  const Transform transform = GetTransform();
  const auto camera = renderer.GetCamera();

  float offset_x = offset_.x;
  float offset_y = offset_.y;
  if (centered_) {
    offset_x -= static_cast<float>(GetWidth()) * 0.5f;
    offset_y -= static_cast<float>(GetHeight()) * 0.5f;
  }

  const glm::vec2 b0 = glm::vec2(0.f + offset_x, 0.f + offset_y);
  const glm::vec2 b2 = glm::vec2(GetWidth() + offset_x, GetHeight() + offset_y);

  const glm::vec2 p0 = transform.TransformPoint(b0);
  const glm::vec2 p2 = transform.TransformPoint(b2);

  const glm::vec2 s0 = camera.WorldToScreen(p0);
  const glm::vec2 s2 = camera.WorldToScreen(p2);

  offset_x *= transform.GetScale().x;
  offset_y *= transform.GetScale().y;

  const float angle = transform.GetRotation();  // Angle of rotation
  const SDL_Point center{                       // Rotate around origin
      static_cast<int>(-offset_x),
      static_cast<int>(-offset_y)};

  const SDL_RendererFlip flip = flip_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  SDL_Rect dst_rect = {
      static_cast<int>(s0.x),
      static_cast<int>(s0.y),
      static_cast<int>(s2.x - s0.x),
      static_cast<int>(s2.y - s0.y)};

  if (nullptr != texture_) {
    SDL_RenderCopyEx(
        renderer.GetSDLRenderer(),
        texture_,
        &src_rect_,
        &dst_rect,
        angle,
        &center,
        flip);
  }

  // Debug...
  SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer.GetSDLRenderer(), &dst_rect);

  if (offset_.x != 0 || offset_.y != 0) {
    SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(
        renderer.GetSDLRenderer(),
        dst_rect.x,
        dst_rect.y + -static_cast<int>(offset_y),
        dst_rect.x + dst_rect.w - 1,
        dst_rect.y + -static_cast<int>(offset_y));
    SDL_RenderDrawLine(
        renderer.GetSDLRenderer(),
        dst_rect.x + -static_cast<int>(offset_x),
        dst_rect.y,
        dst_rect.x + -static_cast<int>(offset_x),
        dst_rect.y + dst_rect.h - 1);
  }
}
