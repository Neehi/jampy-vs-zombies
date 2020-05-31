#ifndef CORE_GAME_STATE_H_
#define CORE_GAME_STATE_H_

#include <cassert>
#include <string>

#include <SDL.h>

#include "graphics/renderer.h"

class Game;
class GameStateManager;
class InputManager;

// GameState represents a stage of a game, i.e. title screen, main menu, pause,
// gameplay, etc. Each state is intended to be isolated from the game engine
// and is responsible for its own assets, input, updating and rendering.
class GameState {
 public:
  GameState() = default;

  // Return the string identifier for this state
  virtual std::string GetID() const = 0;  // XXX: Pass in?

  // Returns a reference to the game
  const Game& GetGame() const;

  // Return a reference to the game's input manager
  const InputManager& GetInputManager() const;

  // Returns a reference to the state manager, which manages state changes
  inline const GameStateManager& GetStateManager() const {
    assert(state_manager_);
    return *state_manager_;
  }

  // Called when this state becomes the active state
  virtual void OnEnter();

  // Called then this state is exited - i.e. moving to another state
  virtual void OnExit();

  // Called each game loop - when the active state
  virtual void OnUpdate(const float delta) = 0;

  // Called each game loop - when the active state
  virtual void OnRender(const Renderer& renderer) = 0;

 private:
  // Should not be called directly (called by GameStateManager)
  inline void SetStateManager(
      GameStateManager& state_manager) {  // NOLINT(runtime/references)
    state_manager_ = &state_manager;
  }

 private:
  GameStateManager* state_manager_{nullptr};

  friend class GameStateManager;
};

#endif  // CORE_GAME_STATE_H_
