#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>

//class Game;

class InputManager {
 public:
  InputManager();
  ~InputManager() = default;

  bool IsKeyPressed(SDL_Scancode key) const;

 private:
  const Uint8* sdl_keyboard_state_;

  void HandleEvent(SDL_Event& event);

  friend class Game;
};

#endif
