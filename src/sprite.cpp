#include "sprite.h"

void Sprite::Render(SDL_Renderer* renderer) const {
  const Transform transform = GetTransform();
  const Vector2f position = transform.GetPosition();

  float offset_x = offset_.x;
  float offset_y = offset_.y;
  if (centered_) {
    offset_x -= (float)GetWidth() * 0.5f;
    offset_y -= (float)GetHeight() * 0.5f;
  }

  float scaled_w = (float)src_rect_.w;
  float scaled_h = (float)src_rect_.h;

  const float scale = transform.GetScale();
  if (scale != 1.0f) {
    offset_x *= scale;
    offset_y *= scale;
    scaled_w *= scale;
    scaled_h *= scale;
  }

  const float angle = transform.GetRotation();  // Angle of rotation
  const SDL_Point center{                       // Rotate around origin
      static_cast<int>(-offset_x),
      static_cast<int>(-offset_y)};

  const SDL_RendererFlip flip = flip_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  SDL_Rect dst_rect = {
      static_cast<int>(position.x + offset_x),
      static_cast<int>(position.y + offset_y),
      static_cast<int>(scaled_w),
      static_cast<int>(scaled_h)};

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
