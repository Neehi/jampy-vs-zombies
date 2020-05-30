#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>

class InputManager {
 public:
  InputManager();
  ~InputManager() = default;

  bool IsKeyPressed(SDL_Scancode key) const;

 private:
  const Uint8* sdl_keyboard_state_;

  void HandleEvent(const SDL_Event& event);

  friend class Game;
};

#endif
