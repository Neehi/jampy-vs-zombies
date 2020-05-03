#include <memory>

#include "game.h"
#include "game_state.h"
#include "texture.h"

class SandboxState : public GameState {
 public:
  using GameState::GameState;

  virtual void OnEnter() override;
  virtual void OnHandleEvent(const SDL_Event* event) override {}
  virtual void OnUpdate() override {}
  virtual void OnRender(SDL_Renderer* renderer) override;
  virtual std::string GetID() const override { return id_; }

 private:
  std::shared_ptr<Texture> jampy_{nullptr};

 private:
  static const std::string id_;
};

const std::string SandboxState::id_ = "Sandbox";

void SandboxState::OnEnter() {
  GameState::OnEnter();
  jampy_ = std::make_shared<Texture>("../res/textures/Knight/knight.png", GetGame().GetSDLRenderer());
}

void SandboxState::OnRender(SDL_Renderer* renderer) {
  const std::size_t w = jampy_->GetWidth();
  const std::size_t h = jampy_->GetHeight();
  SDL_Rect dst_rect{
      static_cast<int>(GetGame().GetScreenWidth() - w) >> 1,
      static_cast<int>(GetGame().GetScreenHeight() -  h) >> 1,
      static_cast<int>(w),
      static_cast<int>(h)};
  jampy_->Render(renderer, &dst_rect);
}

int main(int argc, char *argv[]) {

  Game* game = new Game(640, 480, "Jampy vs Zombies");
  game->SetGameState(std::make_shared<SandboxState>(*game));
  game->Run();
  delete game;

  return 0;
}
