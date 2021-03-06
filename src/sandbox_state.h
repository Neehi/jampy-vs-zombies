#ifndef SANDBOX_STATE_H_
#define SANDBOX_STATE_H_

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

#endif  // SANDBOX_STATE_H_
