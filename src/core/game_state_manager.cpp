#include "core/game_state_manager.h"

#include <iostream>
#include <utility>

void GameStateManager::AddState(std::shared_ptr<GameState> state) {
  std::cout << "GameStateManager: Adding '" << state->GetID() << "'\n";
  auto inserted = states_.insert(std::make_pair(state->GetID(), state));

  if (!inserted.second) {
    std::cerr << "GameStateManager: Error adding '" << state->GetID()
              << "' - a state with this id already exists\n";
    return;
  }

  state->SetStateManager(*this);
}

void GameStateManager::RemoveState(const std::string id) {
  auto it = states_.find(id);
  if (it == states_.end()) {
    std::cout << "GameStateManager: '" << id << "' not found\n";
    return;
  }

  if (active_state_ && id == active_state_->GetID()) {
    active_state_ = nullptr;
  }

  if (pending_state_ && id == pending_state_->GetID()) {
    pending_state_ = nullptr;
  }

  states_.erase(id);
}

void GameStateManager::SetActiveState(const std::string id) {
  auto it = states_.find(id);
  if (it == states_.end()) {
    std::cout << "GameStateManager: '" << id << "' not found\n";
    return;
  }

  if (active_state_ && id == active_state_->GetID()) {
    std::cerr << "GameStateManager: '" << id
              << "' is already the active state\n";
    return;
  }

  pending_state_ = it->second;
}

void GameStateManager::OnUpdate(const float delta) {
  // XXX: Move to a pre-update method?
  if (pending_state_) {
    if (active_state_) {
      active_state_->OnExit();
    }
    active_state_ = pending_state_;
    pending_state_ = nullptr;
    active_state_->OnEnter();
  }

  if (active_state_) {
    active_state_->OnUpdate(delta);
  }
}

void GameStateManager::OnRender(const Renderer& renderer) {
  if (active_state_) {
    active_state_->OnRender(renderer);
  }
}
