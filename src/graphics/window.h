#ifndef GRAPHICS_WINDOW_H_
#define GRAPHICS_WINDOW_H_

#include <cstdint>
#include <string>

struct SDL_Window;

class Window {
 public:
  Window(const std::string& title, const uint32_t width, const uint32_t height);
  ~Window();

  inline uint32_t GetWidth() const { return width_; }
  inline uint32_t GetHeight() const { return height_; }

  inline SDL_Window* GetSDLWindow() const { return sdl_window_; }

 private:
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

 private:
  SDL_Window* sdl_window_{nullptr};
  uint32_t width_;
  uint32_t height_;
};

#endif  // GRAPHICS_WINDOW_H_
