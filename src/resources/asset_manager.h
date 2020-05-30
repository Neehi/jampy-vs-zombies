#ifndef RESOURCES_ASSET_MANAGER_H_
#define RESOURCES_ASSET_MANAGER_H_

#include <map>
#include <string>

#include <SDL.h>

#define DEFAULT_ASSETS_DIR "../res/"
#define DEFAULT_TEXTURES_SUBDIR "textures/"

using TextureMap = std::map<std::string, SDL_Texture*>;

class AssetManager {
 public:
  static AssetManager& Instance() {
    static AssetManager instance;
    return instance;
  }

  void Purge();

  bool LoadTexture(const std::string id,
                   const std::string file_name,
                   SDL_Renderer* renderer);
  inline SDL_Texture* GetTexture(const std::string id) { return textures_[id]; }
  void FreeTexture(const std::string id);

 private:
  AssetManager() = default;
  ~AssetManager();
  AssetManager(const AssetManager&) = delete;
  AssetManager& operator=(const AssetManager&) = delete;

 private:
  std::string assets_dir_{DEFAULT_ASSETS_DIR};
  std::string textures_subdir_{DEFAULT_TEXTURES_SUBDIR};

  TextureMap textures_;
};

#endif  // RESOURCES_ASSET_MANAGER_H_
