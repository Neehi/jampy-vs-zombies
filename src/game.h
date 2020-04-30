#pragma once
#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <string>

#include <SDL.h>

class Game {
 public:
  Game(const std::size_t screen_width, const std::size_t screen_height,
       const std::string& title);
  ~Game();

  void Run();

  inline std::size_t GetScreenWidth() const { return screen_width_; }
  inline std::size_t GetScreenHeight() const { return screen_height_; }

  inline SDL_Window* GetSDLWindow() const { return sdl_window_; }
  inline SDL_Renderer* GetSDLRenderer() const { return sdl_renderer_; }

 protected:
  void HandleEvents();
  void Update();
  void Render();

 private:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

 private:
  SDL_Window* sdl_window_;
  SDL_Renderer* sdl_renderer_;
  std::size_t screen_width_;
  std::size_t screen_height_;

  bool running_{false};
};

#endif
