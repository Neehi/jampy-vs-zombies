#include "game_object.h"

void GameObject::Render(SDL_Renderer* sdl_renderer) {
  if (nullptr != texture_) {
    SDL_Rect dst_rect = {
        static_cast<int>(x_),
        static_cast<int>(y_),
        static_cast<int>(texture_->GetWidth()),
        static_cast<int>(texture_->GetHeight())};
    texture_->Render(sdl_renderer, &dst_rect);
  }
}

void GameObject::SetTexture(const std::shared_ptr<Texture> texture) {
  texture_ = texture;
}
