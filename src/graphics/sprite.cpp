#include "sprite.h"

void Sprite::Render(SDL_Renderer* renderer) const {
  const Transform transform = GetTransform();

  float offset_x = offset_.x;
  float offset_y = offset_.y;
  if (centered_) {
    offset_x -= (float)GetWidth() * 0.5f;
    offset_y -= (float)GetHeight() * 0.5f;
  }

  const glm::vec2 b0 = glm::vec2(0.f + offset_x, 0.f + offset_y);
  const glm::vec2 b2 = glm::vec2(GetWidth() + offset_x, GetHeight() + offset_y);

  const glm::vec2 p0 = transform.TransformPoint(b0);
  const glm::vec2 p2 = transform.TransformPoint(b2);

  offset_x *= transform.GetScale().x;
  offset_y *= transform.GetScale().y;

  const float angle = transform.GetRotation();  // Angle of rotation
  const SDL_Point center{                       // Rotate around origin
      static_cast<int>(-offset_x),
      static_cast<int>(-offset_y)};

  const SDL_RendererFlip flip = flip_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  SDL_Rect dst_rect = {
      static_cast<int>(p0.x),
      static_cast<int>(p0.y),
      static_cast<int>(p2.x - p0.x),
      static_cast<int>(p2.y - p0.y)};

  if (nullptr != texture_) {
    SDL_RenderCopyEx(
        renderer,
        texture_,
        &src_rect_,
        &dst_rect,
        angle,
        &center,
        flip);
  }

  // Debug...
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &dst_rect);

  if (offset_.x != 0 || offset_.y != 0) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(
        renderer,
        dst_rect.x,
        dst_rect.y + -static_cast<int>(offset_y),
        dst_rect.x + dst_rect.w - 1,
        dst_rect.y + -static_cast<int>(offset_y));
    SDL_RenderDrawLine(
        renderer,
        dst_rect.x + -static_cast<int>(offset_x),
        dst_rect.y,
        dst_rect.x + -static_cast<int>(offset_x),
        dst_rect.y + dst_rect.h - 1);
  }
}
