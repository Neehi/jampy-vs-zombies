#include <map>
#include <memory>
#include <string>

#include "asset_manager.h"
#include "game.h"
#include "game_state.h"
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
    {"knight_idle12", "Knight/idle/idle12.png"}};

class SandboxState : public GameState {
 public:
  using GameState::GameState;

  virtual void OnEnter() override;
  virtual void OnHandleEvent(const SDL_Event* event) override {}
  virtual void OnUpdate(const float delta) override;
  virtual void OnRender(SDL_Renderer* renderer) override;
  virtual std::string GetID() const override { return id_; }

 private:
  std::shared_ptr<Player> jampy_;

 private:
  static const std::string id_;
};

const std::string SandboxState::id_ = "Sandbox";

void SandboxState::OnEnter() {
  GameState::OnEnter();
  for (auto it = player_textures.begin(); it != player_textures.end(); it++) {
    AssetManager::Instance().LoadTexture(
        it->first,
        it->second,
        GetGame().GetSDLRenderer());
  }
  jampy_ = std::make_shared<Player>(this, "knight", 128, 128);
}

void SandboxState::OnUpdate(const float delta) {
  jampy_->Update(delta);
}

void SandboxState::OnRender(SDL_Renderer* renderer) {
  jampy_->Render(renderer);
}

int main(int argc, char *argv[]) {

  Game* game = new Game(640, 480, "Jampy vs Zombies");
  game->SetGameState(std::make_shared<SandboxState>(*game));
  game->Run();
  delete game;

  return 0;
}
