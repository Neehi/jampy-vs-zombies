#include <algorithm>
#include <memory>

#include "game.h"
#include "game_object.h"
#include "game_state.h"
#include "texture.h"

class GameState;

class Player : public GameObject {
 public:
  using GameObject::GameObject;
  Player(GameState* game_state)
      : GameObject(), game_state_(game_state), dx_(60), dy_(0) {
    const auto h = game_state->GetGame().GetScreenHeight();
    x_ = -18;
    y_ = h - 110;
  }

  void Update(const float delta) {
    const auto& input = game_state_->GetGame().GetInputManager();
    if (input.IsKeyPressed(SDL_SCANCODE_LEFT)) {
      x_ = std::max((float)-18, x_ - dx_ * delta);
    }
    if (input.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
      x_ = std::min((float)(640 - 82), x_ + dx_ * delta);
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
  std::shared_ptr<Texture> tex_{nullptr};
  std::shared_ptr<Player> jampy_ = std::make_shared<Player>(this);

 private:
  static const std::string id_;
};

const std::string SandboxState::id_ = "Sandbox";

void SandboxState::OnEnter() {
  GameState::OnEnter();
  tex_ = std::make_shared<Texture>("../res/textures/Knight/knight.png", GetGame().GetSDLRenderer());
  jampy_->SetTexture(tex_);
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
