#include <memory>

#include "core/game.h"
#include "core/game_state.h"
#include "sandbox_state.h"

int main(int argc, char *argv[]) {

  Game* game = new Game(640, 480, "Jampy vs Zombies");
  game->SetGameState(std::make_shared<SandboxState>(*game));
  game->Run();
  delete game;

  return 0;
}
