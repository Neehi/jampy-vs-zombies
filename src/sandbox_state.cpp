#include "sandbox_state.h"

#include <map>
#include <memory>

#include "core/game.h"
#include "core/game_object.h"
#include "resources/asset_manager.h"
#include "player.h"

using TextureList = std::map<std::string, std::string>;

const TextureList player_textures = {
    {"knight", "Knight/knight.png"},
    {"knight_idle01", "Knight/idle/idle1.png"},
    {"knight_idle02", "Knight/idle/idle2.png"},
    {"knight_idle03", "Knight/idle/idle3.png"},
    {"knight_idle04", "Knight/idle/idle4.png"},
    {"knight_idle05", "Knight/idle/idle5.png"},
    {"knight_idle06", "Knight/idle/idle6.png"},
    {"knight_idle07", "Knight/idle/idle7.png"},
    {"knight_idle08", "Knight/idle/idle8.png"},
    {"knight_idle09", "Knight/idle/idle9.png"},
    {"knight_idle10", "Knight/idle/idle10.png"},
    {"knight_idle11", "Knight/idle/idle11.png"},
    {"knight_idle12", "Knight/idle/idle12.png"},
    {"knight_walk01", "Knight/Walk/walk1.png"},
    {"knight_walk02", "Knight/Walk/walk2.png"},
    {"knight_walk03", "Knight/Walk/walk3.png"},
    {"knight_walk04", "Knight/Walk/walk4.png"},
    {"knight_walk05", "Knight/Walk/walk5.png"},
    {"knight_walk06", "Knight/Walk/walk6.png"}};

const std::string SandboxState::id_ = "Sandbox";

void SandboxState::OnEnter() {
  GameState::OnEnter();
  for (auto it = player_textures.begin(); it != player_textures.end(); it++) {
    AssetManager::Instance().LoadTexture(
        it->first, it->second,
        GetGame().GetSDLRenderer());
  }
  std::shared_ptr<GameObject> jampy =
      std::make_shared<Player>(this, "knight", 128, 128);
  game_objects_.Add(jampy);
  // Load tileset
  AssetManager::Instance().LoadTexture(
      "tileset",
      "tilesets/Tileset.png",
      GetGame().GetSDLRenderer());
  std::shared_ptr<GameObject> tileset =
      std::make_shared<GameObject>("tileset", 288, 192);
  tileset->SetCentered(false);
  game_objects_.Add(tileset);
}

void SandboxState::OnUpdate(const float delta) { game_objects_.Update(delta); }

void SandboxState::OnRender(SDL_Renderer* renderer) {
  game_objects_.Render(renderer);
}
