#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <cstddef>
#include <string>
#include <vector>

#include "game_object.h"
#include "game_state.h"

class Player : public GameObject {
  std::vector<std::string> player_idle_animations = {
      "knight_idle01", "knight_idle02", "knight_idle03", "knight_idle04",
      "knight_idle05", "knight_idle06", "knight_idle07", "knight_idle08",
      "knight_idle09", "knight_idle10", "knight_idle11", "knight_idle12"};

 public:
  Player(GameState* game_state, const std::string template_id,
         const std::size_t width, const std::size_t height);
  ~Player() = default;

  void Update(const float delta);

 private:
  GameState* game_state_;
  float dx_{0};
  float dy_{0};

  std::vector<std::string>* current_sequence_ = &player_idle_animations;
  int current_frame_ = 0;  // XXX: Needed?
};

#endif
