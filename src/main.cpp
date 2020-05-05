#include <memory>

#include "game.h"
#include "game_object.h"
#include "game_state.h"
#include "texture.h"

class Player : public GameObject {
 public:
  using GameObject::GameObject;
  Player() : GameObject(), dx_(60), dy_(0) {}

  void Update(const float delta) {
    x_ += dx_ * delta;
    if (x_ < 0) {
      x_ = 0;
      dx_ = -dx_;
    } else if (x_ > 640 - 64) {
      x_ = 640-64;
      dx_ = -dx_;
    }
  }

 private:
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
  std::shared_ptr<Player> jampy_ = std::make_shared<Player>();

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
