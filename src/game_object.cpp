#include "game_object.h"

#include "asset_manager.h"
#include "vector2.h"

GameObject::GameObject(const std::string texture_id,
                       const float x,  const float y,
                       const std::size_t width,
                       const std::size_t height)
    : width_(width), height_(height) {
  SetTexture(texture_id);
  transform_ = Transform(Vector2f(x, y));
}

void GameObject::Render(SDL_Renderer* renderer) {
  const SDL_Rect src_rect = {
      static_cast<int>(clip_x_),
      static_cast<int>(clip_y_),
      static_cast<int>(width_),
      static_cast<int>(height_)};
  const SDL_Rect dst_rect = {
      static_cast<int>(transform_.GetPosition().x),
      static_cast<int>(transform_.GetPosition().y),
      static_cast<int>(width_),
      static_cast<int>(height_)};
  if (nullptr != texture_) {
    SDL_RenderCopy(renderer, texture_, &src_rect, &dst_rect);
  }
  // Debug...
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &dst_rect);
}

void GameObject::SetTexture(const std::string texture_id) {
  texture_ = AssetManager::Instance().GetTexture(texture_id);
}
