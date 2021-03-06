#include "graphics/renderer.h"

#include <iostream>

#include <SDL.h>

#include "graphics/drawable.h"

Renderer::Renderer(const Window& window)
    : window_(&window) {
  std::cout << "Renderer: Creating SDL rendering context\n";
  sdl_renderer_ = SDL_CreateRenderer(
      window.GetSDLWindow(),
      -1,
      SDL_RENDERER_ACCELERATED);

  if (nullptr == sdl_renderer_) {
    std::cerr << "Renderer: Error creating SDL rendering context - "
              << SDL_GetError() << "\n";
    // TODO(Neehi): Error handling
  }

  default_camera_ = std::make_unique<OrthographicCamera>(
      window_->GetWidth(),
      window_->GetHeight());
  default_camera_->GetTransform().SetPosition(
      glm::vec2(
          static_cast<float>(window_->GetWidth()) * 0.5f,
          static_cast<float>(window_->GetHeight()) * 0.5f));
}

Renderer::~Renderer() {
  std::cout << "Renderer: Destroying SDL rendering context\n";
  SDL_DestroyRenderer(sdl_renderer_);
}

void Renderer::BeginScene() {
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl_renderer_);
}

void Renderer::EndScene() {
  SDL_RenderPresent(sdl_renderer_);  // XXX: Move to window?
}

void Renderer::Draw(const Drawable& drawable) {
  // TODO(Neehi): Pass transform
  drawable.Render(*this);
}
