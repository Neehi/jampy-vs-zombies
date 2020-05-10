#include "sprite.h"

void Sprite::Render(SDL_Renderer* renderer) const {
  const Transform transform = GetTransform();
  const Vector2f position = transform.GetPosition();

  const float angle = transform.GetRotation();  // Angle of rotation
  const SDL_Point center = SDL_Point{0, 0};  // Rotate around the origin
  const float scale = transform.GetScale();

  const SDL_Rect dst_rect = {
      static_cast<int>(position.x),
      static_cast<int>(position.y),
      static_cast<int>(src_rect_.w * scale),
      static_cast<int>(src_rect_.h * scale)};

  if (nullptr != texture_) {
    SDL_RenderSetScale(renderer, GetScale(), GetScale());
    SDL_RenderCopyEx(
        renderer,
        texture_,
        &src_rect_,
        &dst_rect,
        angle,
        &center,
        SDL_FLIP_NONE);
  }

  // Debug...
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &dst_rect);
}
