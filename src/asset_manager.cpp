#include "asset_manager.h"

#include <iostream>

#include <SDL_image.h>

AssetManager::~AssetManager() {
  Purge();
}

void AssetManager::Purge() {
  if (!textures_.empty()) {
    std::cout << "AssetManager: Purging textures...\n";
    for (TextureMap::iterator it = textures_.begin();
         it != textures_.end();
         it++) {
      std::cout << "AssetManager: Deleting texure '" << it->first << "'\n";
      SDL_DestroyTexture(it->second);
    }
    textures_.clear();
    std::cout << "AssetManager: All textures deleted\n";
  }
}

bool AssetManager::LoadTexture(const std::string id,
                               const std::string file_name,
                               SDL_Renderer* renderer) {
  if (textures_.count(id) > 0) {
    std::cout << "AssetManager: Texture '" << id << "' already loaded\n";
    return true;
  }

  const std::string file = assets_dir_ + textures_subdir_ + file_name;

  std::cout << "AssetManager: Loading texture '" << id << "' from " << file
            << "\n";

  SDL_Surface* surface = IMG_Load(file.c_str());

  if (NULL == surface) {
    std::cout << "AssetManager: Error loading surface for '" << id
              << "' - " << IMG_GetError() << "\n";
    return false;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  if (NULL == texture) {
    std::cout << "AssetManager: Error creating texture '" << id
              << "' - " << IMG_GetError()<< "\n";
    return false;
  }

  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  std::cout << "AssetManager: Texture '" << id << "' loaded (" << w << "x" << h
            << ")\n";

  textures_[id] = texture;

  return true;
}

void AssetManager::FreeTexture(const std::string id) {
  SDL_Texture* texture = GetTexture(id);

  if (NULL == texture) {
    std::cout << "AssetManager: Texture '" << id << "' not loaded\n";
    return;
  }

  std::cout << "AssetManager: Deleting texture '" << id << "'\n";
  SDL_DestroyTexture(texture);
  textures_.erase(id);
}
