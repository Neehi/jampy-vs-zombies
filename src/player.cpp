#include "player.h"

#include <algorithm>

#include "asset_manager.h"
#include "game.h"
#include "vector2.h"

Player::Player(GameState* game_state, const std::string template_id,
               const std::size_t width, const std::size_t height)
    : GameObject(template_id, width, height),
      game_state_(game_state),
      dx_(60), dy_(0) {
  const auto h = game_state->GetGame().GetScreenHeight();
  SetPosition(Vector2f(0, h - static_cast<float>(height)));
}

void Player::Update(const float delta) {
  // Handle player input
  const auto& input = game_state_->GetGame().GetInputManager();
  Vector2f position = GetPosition();
  if (input.IsKeyPressed(SDL_SCANCODE_LEFT)) {
    position.x = std::max((float)0, position.x - dx_ * delta);
  }
  if (input.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
    position.x = std::min((float)(640 - 128), position.x + dx_ * delta);
  }
  SetPosition(position);
  // Update animation
  const std::size_t frame_count = current_sequence_->size();
  current_frame_ = (SDL_GetTicks() / 80) % frame_count;
  SetTexture(AssetManager::Instance().GetTexture(current_sequence_->at(current_frame_)));
}
