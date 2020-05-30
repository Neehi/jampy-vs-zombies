#ifndef CORE_GAME_STATE_MANAGER_H_
#define CORE_GAME_STATE_MANAGER_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "core/game_state.h"

union SDL_Event;

class Game;

class GameStateManager {
 public:
  explicit GameStateManager(Game& game) : game_(&game) {}
  ~GameStateManager() = default;

  inline Game& GetGame() const { return *game_; }

  void AddState(std::shared_ptr<GameState> state);
  void RemoveState(const std::string id);
  void SetActiveState(const std::string id);

  void OnUpdate(const float delta);
  void OnRender(const Renderer& renderer);

 private:
  Game* game_;
  std::unordered_map<std::string, std::shared_ptr<GameState>> states_;
  std::shared_ptr<GameState> active_state_{nullptr};
  std::shared_ptr<GameState> pending_state_{nullptr};
};

#endif  // CORE_GAME_STATE_MANAGER_H_
