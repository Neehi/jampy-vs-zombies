#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "graphics/window.h"

struct SDL_Renderer;

class Drawable;

class Renderer {
 public:
  explicit Renderer(const Window& window);
  ~Renderer();

  void BeginScene();
  void EndScene();

  void Draw(const Drawable& drawable);

  inline const Window& GetWindow() const { return *window_; }
  inline SDL_Renderer* GetSDLRenderer() const { return sdl_renderer_; }

 public:
  const Window* window_;
  SDL_Renderer* sdl_renderer_{nullptr};
};

#endif
