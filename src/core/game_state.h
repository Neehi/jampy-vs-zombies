#ifndef CORE_GAME_STATE_H_
#define CORE_GAME_STATE_H_

#include <cassert>
#include <string>

#include <SDL.h>

#include "graphics/renderer.h"

class GameStateManager;

// GameState represents a stage of a game, i.e. title screen, main menu, pause,
// gameplay, etc. Each state is intended to be isolated from the game engine
// and is responsible for its own assets, input, updating and rendering.
class GameState {
 public:
  GameState() = default;

  inline GameStateManager& GetStateManager() const {
    assert(state_manager_);
    return *state_manager_;
  }

  virtual void OnEnter();
  virtual void OnExit();

  virtual void OnUpdate(const float delta) = 0;
  virtual void OnRender(const Renderer& renderer) = 0;

  virtual std::string GetID() const = 0;

 private:
  inline void SetStateManager(
      GameStateManager& state_manager) {  // NOLINT(runtime/references)
    state_manager_ = &state_manager;
  }

 private:
  GameStateManager* state_manager_{nullptr};

  friend class GameStateManager;
};

#endif  // CORE_GAME_STATE_H_
