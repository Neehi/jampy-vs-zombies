#include "game.h"

#include <iostream>

Game::Game(const std::size_t screen_width, const std::size_t screen_height,
           const std::string& title)
    : screen_width_(screen_width), screen_height_(screen_height) {
  // Initializing SDL
  std::cout << "Initializing SDL\n";
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Create SDL window
  std::cout << "Creating window (" << screen_width << "x" << screen_height
            << ")\n";
  sdl_window_ = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      static_cast<int>(screen_width),
      static_cast<int>(screen_height),
      SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_) {
    std::cerr << "Error creating window: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Create SDL renderer
  std::cout << "Creating renderer\n";
  sdl_renderer_ = SDL_CreateRenderer(
      sdl_window_,
      -1,
      SDL_RENDERER_ACCELERATED);

  if (nullptr == sdl_renderer_) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Set game running
  running_ = true;
}

Game::~Game() {
  // Shutdown SDL
  std::cout << "Shutting down SDL\n";
  SDL_DestroyRenderer(sdl_renderer_);
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

void Game::HandleEvents() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        std::cout << "Received SDL_Quit event\n";
        running_ = false;
        break;
      default:
        break;
    }
  }
}

void Game::Update() {
  // ...
}

void Game::Render() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl_renderer_);

  // Update screen
  SDL_RenderPresent(sdl_renderer_);
}

void Game::Run() {
  running_ = true;
  while (running_) {
    HandleEvents();
    Update();
    Render();
  }

}
