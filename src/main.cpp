#include "SDL.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return 1;
  }

  window = SDL_CreateWindow(
      "Jampy vs Zombies",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      SDL_WINDOW_SHOWN);

  if (nullptr != window) {
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }

  SDL_Quit();

  return 0;
}
