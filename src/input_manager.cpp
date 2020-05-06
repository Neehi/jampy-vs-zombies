#include "input_manager.h"

#include <iostream>

InputManager::InputManager() {
  sdl_keyboard_state_ = SDL_GetKeyboardState(NULL);
}

bool InputManager::IsKeyPressed(SDL_Scancode key) const {
  return sdl_keyboard_state_ != nullptr &&
         sdl_keyboard_state_[key] == 1;
}

void InputManager::HandleEvent(SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYDOWN: {
      const SDL_Scancode scancode = event.key.keysym.scancode;
      std::cout << SDL_GetScancodeName(scancode) << " key pressed ("
                << IsKeyPressed(scancode) << ")\n";
      break;
    }
    case SDL_KEYUP: {
      const SDL_Scancode scancode = event.key.keysym.scancode;
      std::cout << SDL_GetScancodeName(scancode) << " key released ("
                << IsKeyPressed(scancode) << ")\n";
      break;
    }
  }
}
