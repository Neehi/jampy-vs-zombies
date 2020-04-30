#include "game.h"

int main(int argc, char *argv[]) {

  Game* game = new Game(640, 480, "Jampy vs Zombies");
  game->Run();
  delete game;

  return 0;
}
