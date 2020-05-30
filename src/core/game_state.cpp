#include "core/game_state.h"

#include <iostream>

void GameState::OnEnter() {
  std::cout << "GameState: Entering '" << GetID() << "' state\n";
}

void GameState::OnExit() {
  std::cout << "GameState: Exiting '" << GetID() << "' state\n";
}
