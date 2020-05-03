#include <memory>

#include "game.h"
#include "game_state.h"

class SandboxState : public GameState {
 public:
  using GameState::GameState;

  virtual void OnHandleEvent(const SDL_Event* event) override {}
  virtual void OnUpdate() override {}
  virtual void OnRender(SDL_Renderer* renderer) override {}
  virtual std::string GetID() const override { return id_; }

 private:
  static const std::string id_;
};

const std::string SandboxState::id_ = "Sandbox";

int main(int argc, char *argv[]) {

  Game* game = new Game(640, 480, "Jampy vs Zombies");
  game->SetGameState(std::make_shared<SandboxState>(*game));
  game->Run();
  delete game;

  return 0;
}
