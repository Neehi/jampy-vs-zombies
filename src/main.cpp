#include <memory>

#include "core/game.h"
#include "core/game_state.h"
#include "sandbox_state.h"  // NOLINT(build/include_subdir)

int main(int argc, char *argv[]) {
  Game* game = new Game(640, 480, "Jampy vs Zombies");
  game->GetStateManager().AddState(std::make_shared<SandboxState>());
  game->GetStateManager().SetActiveState("Sandbox");
  game->Run();
  delete game;

  return 0;
}
