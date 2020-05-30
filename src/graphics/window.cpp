#include "graphics/window.h"

#include <iostream>

#include <SDL.h>

Window::Window(const std::string& title,
               const uint32_t width,
               const uint32_t height)
    : width_(width), height_(height) {
  std::cout << "Window: Initializing SDL video subsystem\n";
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Window: Error initializing SDL video subsystem - "
              << SDL_GetError() << "\n";
    // TODO(Neehi): Error handling
  }

  std::cout << "Window: Creating SDL window (" << width << "x" << height
            << ")\n";
  sdl_window_ = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      static_cast<int>(width),
      static_cast<int>(height),
      SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_) {
    std::cerr << "Error creating SDL window - " << SDL_GetError() << "\n";
    // TODO(Neehi): Error handling
  }
}

Window::~Window() {
  std::cout << "Window: Destroying SDL window\n";
  SDL_DestroyWindow(sdl_window_);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
