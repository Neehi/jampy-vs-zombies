#include <algorithm>
#include <memory>

#include "asset_manager.h"
#include "game.h"
#include "game_object.h"
#include "game_state.h"

class GameState;

class Player : public GameObject {
 public:
  Player(GameState* game_state, const std::string template_id,
         const std::size_t width, const std::size_t height)
      : GameObject(template_id, width, height),
        game_state_(game_state),
        dx_(60), dy_(0) {
    const auto h = game_state->GetGame().GetScreenHeight();
    x_ = 0;
    y_ = h - 128;
  }

  void Update(const float delta) {
    const auto& input = game_state_->GetGame().GetInputManager();
    if (input.IsKeyPressed(SDL_SCANCODE_LEFT)) {
      x_ = std::max((float)0, x_ - dx_ * delta);
    }
    if (input.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
      x_ = std::min((float)(640 - 128), x_ + dx_ * delta);
    }
  }

 private:
  GameState* game_state_;
  float dx_{0};
  float dy_{0};
};

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
