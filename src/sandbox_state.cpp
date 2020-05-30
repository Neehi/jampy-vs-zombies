#include "sandbox_state.h"  // NOLINT(build/include_subdir)

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <glm/vec2.hpp>

#include "core/game.h"
#include "core/game_object.h"
#include "graphics/window.h"
#include "resources/asset_manager.h"
#include "tilemap/tile.h"
#include "player.h"  // NOLINT(build/include_subdir)

using TextureList = std::map<std::string, std::string>;

const TextureList player_textures = {
    {"knight", "Knight/knight.png"},
    {"knight_idle01", "Knight/Idle/idle1.png"},
    {"knight_idle02", "Knight/Idle/idle2.png"},
    {"knight_idle03", "Knight/Idle/idle3.png"},
    {"knight_idle04", "Knight/Idle/idle4.png"},
    {"knight_idle05", "Knight/Idle/idle5.png"},
    {"knight_idle06", "Knight/Idle/idle6.png"},
    {"knight_idle07", "Knight/Idle/idle7.png"},
    {"knight_idle08", "Knight/Idle/idle8.png"},
    {"knight_idle09", "Knight/Idle/idle9.png"},
    {"knight_idle10", "Knight/Idle/idle10.png"},
    {"knight_idle11", "Knight/Idle/idle11.png"},
    {"knight_idle12", "Knight/Idle/idle12.png"},
    {"knight_walk01", "Knight/Walk/walk1.png"},
    {"knight_walk02", "Knight/Walk/walk2.png"},
    {"knight_walk03", "Knight/Walk/walk3.png"},
    {"knight_walk04", "Knight/Walk/walk4.png"},
    {"knight_walk05", "Knight/Walk/walk5.png"},
    {"knight_walk06", "Knight/Walk/walk6.png"}};

const char* SandboxState::id_ = "Sandbox";

void SandboxState::OnEnter() {
  GameState::OnEnter();
  Window& window = GetStateManager().GetGame().GetWindow();
  Renderer& renderer = GetStateManager().GetGame().GetRenderer();
  for (auto it = player_textures.begin(); it != player_textures.end(); it++) {
    AssetManager::Instance().LoadTexture(
        it->first, it->second,
        renderer.GetSDLRenderer());
  }
  std::shared_ptr<GameObject> jampy =
      std::make_shared<Player>(this, "knight", 128, 128);
  jampy->GetTransform().SetPosition(
      jampy->GetTransform().GetPosition() - glm::vec2(0, 32));
  game_objects_.Add(jampy);
  // Load tileset
  AssetManager::Instance().LoadTexture(
      "tileset",
      "tilesets/Tileset.png",
      renderer.GetSDLRenderer());
  tile_set_ = std::make_shared<TileSet>("Sandbox", "tileset", 32, 32, 54, 9);
  std::cout << *tile_set_ << "\n";
  // Setup tile layer
  tile_layer_ = std::make_shared<TileLayer>(
      "Tile Layer 1",
      100, window.GetHeight() / 32,
      32, 32);
  tile_layer_->AddTileSet(tile_set_);
  std::cout << *tile_layer_ << "\n";
  const std::vector<std::size_t> tiles{
      1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, 1, 2, 2, 2, 2, 2, 2,
      3, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
  for (int i = 0; i < 20; i++) {
    const std::size_t n = tiles[i];
    if (n != 0) {
      const Tile tile = tile_set_->GetTile(n - 1);
      tile_layer_->SetTile(i, window.GetHeight() / 32 - 1, n);
    }
  }
}

void SandboxState::OnUpdate(const float delta) { game_objects_.Update(delta); }

void SandboxState::OnRender(const Renderer& renderer) {
  game_objects_.Render(renderer);
  tile_layer_->Render(renderer);
}
