#include "game_object.h"

#include "asset_manager.h"

void GameObject::Render(SDL_Renderer* sdl_renderer) {
  if (nullptr != texture_) {
    int w, h;
    SDL_QueryTexture(texture_, NULL, NULL, &w, &h);
    SDL_Rect dst_rect = {
        static_cast<int>(x_),
        static_cast<int>(y_),
        static_cast<int>(w),
        static_cast<int>(h)};
    SDL_RenderCopy(sdl_renderer, texture_, NULL, &dst_rect);
  }
}

void GameObject::SetTexture(const std::string id) {
  texture_ = AssetManager::Instance().GetTexture(id);
}
