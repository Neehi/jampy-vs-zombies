#include <memory>
#include <string>

#include "asset_manager.h"
#include "game.h"
#include "game_state.h"
#include "player.h"

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
  AssetManager::Instance().LoadTexture(
      "knight",
      "knight/knight.png",
      GetGame().GetSDLRenderer());
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
