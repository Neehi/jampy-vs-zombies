#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include <memory>

#include "graphics/orthographic_camera.h"
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

  inline const OrthographicCamera& GetCamera() const {
    return *default_camera_;
  }

 public:
  const Window* window_;
  SDL_Renderer* sdl_renderer_{nullptr};
  std::unique_ptr<OrthographicCamera> default_camera_;
};

#endif  // GRAPHICS_RENDERER_H_
