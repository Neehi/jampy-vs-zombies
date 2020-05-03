#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

#include <SDL.h>

// GameState represents a stage of a game, i.e. title screen, main menu, pause,
// gameplay, etc. Each state is intended to be isolated from the game engine
// and is responsible for its own assets, input, updating and rendering.
class GameState {
 public:
  virtual void OnEnter();
  virtual void OnExit();

  virtual void OnHandleEvent(const SDL_Event* event) = 0;
  virtual void OnUpdate() = 0;
  virtual void OnRender(SDL_Renderer* renderer) = 0;

  virtual std::string GetID() const = 0;
};

#endif
