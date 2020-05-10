#include "game_object.h"

#include "asset_manager.h"

GameObject::GameObject(const std::string texture_id,
                       const float x,  const float y,
                       const std::size_t width,
                       const std::size_t height)
    : Sprite() {
  SetTexture(AssetManager::Instance().GetTexture(texture_id));
  SetTextureRect(SDL_Rect{0, 0, static_cast<int>(width), static_cast<int>(height)});
  SetPosition(x, y);
}
