#include "core/game_state.h"

#include <iostream>

#include "core/game.h"
#include "core/game_state_manager.h"
#include "input/input_manager.h"

const Game& GameState::GetGame() const {
  return state_manager_->GetGame();
}

const InputManager& GameState::GetInputManager() const {
  return GetGame().GetInputManager();
}

void GameState::OnEnter() {
  std::cout << "GameState: Entering '" << GetID() << "' state\n";
}

void GameState::OnExit() {
  std::cout << "GameState: Exiting '" << GetID() << "' state\n";
}
