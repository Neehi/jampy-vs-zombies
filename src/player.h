#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <cstddef>
#include <string>

#include "game_object.h"
#include "game_state.h"

class Player : public GameObject {
 public:
  Player(GameState* game_state, const std::string template_id,
         const std::size_t width, const std::size_t height);
  ~Player() = default;

  void Update(const float delta);

 private:
  GameState* game_state_;
  float dx_{0};
  float dy_{0};
};

#endif
