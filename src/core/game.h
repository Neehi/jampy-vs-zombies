#pragma once
#ifndef GAME_H
#define GAME_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "graphics/window.h"
#include "input/input_manager.h"
#include "game_state.h"

class Game {
  static const uint32_t kDefaultFrameRate = 60;

 public:
  Game(const std::size_t screen_width, const std::size_t screen_height,
       const std::string& title);
  ~Game();

  void Run();

  void SetGameState(std::shared_ptr<GameState> state);

  inline Window& GetWindow() const { return *window_; }
  inline SDL_Renderer* GetSDLRenderer() const { return sdl_renderer_; }

  inline std::uint32_t GetFPS() const { return fps_; }

  inline InputManager& GetInputManager() const { return *input_manager_; }

 protected:
  void HandleEvents();
  void Update(const float delta);
  void Render();

 private:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

 private:
  std::unique_ptr<Window> window_;
  SDL_Renderer* sdl_renderer_;

  uint32_t frame_rate_{kDefaultFrameRate};
  uint32_t fps_{0};

  std::unique_ptr<InputManager> input_manager_;

  bool running_{false};

  std::shared_ptr<GameState> current_state_{nullptr};
};

#endif
