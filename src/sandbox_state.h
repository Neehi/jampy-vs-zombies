#pragma once
#ifndef SANDBOX_STATE_H
#define SANDBOX_STATE_H

#include <string>

#include "core/game_object_collection.h"
#include "core/game_state.h"

union SDL_Event;
struct SDL_Renderer;

class SandboxState : public GameState {
 public:
  using GameState::GameState;

  virtual void OnEnter() override;
  virtual void OnHandleEvent(const SDL_Event* event) override {}
  virtual void OnUpdate(const float delta) override;
  virtual void OnRender(SDL_Renderer* renderer) override;
  virtual std::string GetID() const override { return id_; }

 private:
  GameObjectCollection game_objects_;

 private:
  static const std::string id_;
};

#endif
