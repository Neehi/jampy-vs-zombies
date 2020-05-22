#pragma once
#ifndef SANDBOX_STATE_H
#define SANDBOX_STATE_H

#include <memory>
#include <string>

#include "core/game_object_collection.h"
#include "core/game_state.h"
#include "tilemap/tile_layer.h"
#include "tilemap/tile_set.h"

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
  std::shared_ptr<TileLayer> tile_layer_{nullptr};
  std::shared_ptr<TileSet> tile_set_{nullptr};

 private:
  static const std::string id_;
};

#endif
