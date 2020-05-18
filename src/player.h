#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "core/game_object.h"
#include "core/game_state.h"
#include "graphics/animation.h"
#include "graphics/animation_player.h"

struct SDL_Renderer;

enum class PlayerState { kIdle = 0, kWalk };

enum class PlayerDirection { kNone = 0, kLeft, kRight };

class Player : public GameObject {
 private:
  std::shared_ptr<Animation> player_idle_animation =
      std::make_shared<Animation>(
          "player_idle",
          std::vector<AnimationFrame>{
             {"knight_idle01", 0, 0, 128, 128},
             {"knight_idle02", 0, 0, 128, 128},
             {"knight_idle03", 0, 0, 128, 128},
             {"knight_idle04", 0, 0, 128, 128},
             {"knight_idle05", 0, 0, 128, 128},
             {"knight_idle06", 0, 0, 128, 128},
             {"knight_idle07", 0, 0, 128, 128},
             {"knight_idle08", 0, 0, 128, 128},
             {"knight_idle09", 0, 0, 128, 128},
             {"knight_idle10", 0, 0, 128, 128},
             {"knight_idle11", 0, 0, 128, 128},
             {"knight_idle12", 0, 0, 128, 128}},
          8.0f);
  std::shared_ptr<Animation> player_walk_animation =
      std::make_shared<Animation>(
          "player_walk",
          std::vector<AnimationFrame>{
              {"knight_walk01", 0, 0, 128, 128},
              {"knight_walk02", 0, 0, 128, 128},
              {"knight_walk03", 0, 0, 128, 128},
              {"knight_walk04", 0, 0, 128, 128},
              {"knight_walk05", 0, 0, 128, 128},
              {"knight_walk06", 0, 0, 128, 128}},
          15.0f);

 public:
  Player(GameState* game_state, const std::string template_id,
         const std::size_t width, const std::size_t height);
  ~Player() = default;

  void Update(const float delta);
  virtual void Render(SDL_Renderer* renderer) const override;

 private:
  void HandleInput();
  void HandleMovement(const float delta);
  void HandleAnimation(const float delta);

 private:
  GameState* game_state_;
  float dx_{0};
  float dy_{0};
  std::size_t width_{48};
  std::size_t height_{52};

  PlayerState state_{PlayerState::kIdle};
  PlayerDirection direction_{PlayerDirection::kNone};

  AnimationPlayer animation_player_;
};

#endif
