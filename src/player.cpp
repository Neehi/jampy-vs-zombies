#include "player.h"

#include <algorithm>

#include "game.h"

Player::Player(GameState* game_state, const std::string template_id,
               const std::size_t width, const std::size_t height)
    : GameObject(template_id, width, height),
      game_state_(game_state),
      dx_(60), dy_(0) {
  const auto h = game_state->GetGame().GetScreenHeight();
  x_ = 0;
  y_ = h - static_cast<float>(height);
}


void Player::Update(const float delta) {
  // Handle player input
  const auto& input = game_state_->GetGame().GetInputManager();
  if (input.IsKeyPressed(SDL_SCANCODE_LEFT)) {
    x_ = std::max((float)0, x_ - dx_ * delta);
  }
  if (input.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
    x_ = std::min((float)(640 - 128), x_ + dx_ * delta);
  }
  // Update animation
  const std::size_t frame_count = current_sequence_->size();
  current_frame_ = (SDL_GetTicks() / 80) % frame_count;
  SetTexture(current_sequence_->at(current_frame_));
}
