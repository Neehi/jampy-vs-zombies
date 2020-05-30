#pragma once
#ifndef SANDBOX_STATE_H
#define SANDBOX_STATE_H

#include <memory>
#include <string>

#include "core/game_object_collection.h"
#include "core/game_state.h"
#include "graphics/renderer.h"
#include "tilemap/tile_layer.h"
#include "tilemap/tile_set.h"

union SDL_Event;

class SandboxState : public GameState {
 public:
  using GameState::GameState;

  void OnEnter() override;
  void OnHandleEvent(const SDL_Event* event) override {}
  void OnUpdate(const float delta) override;
  void OnRender(const Renderer& renderer) override;
  inline std::string GetID() const override { return id_; }

 private:
  GameObjectCollection game_objects_;
  std::shared_ptr<TileLayer> tile_layer_{nullptr};
  std::shared_ptr<TileSet> tile_set_{nullptr};

 private:
  static const char* id_;
};

#endif
