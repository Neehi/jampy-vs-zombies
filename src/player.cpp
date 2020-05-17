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
  animation_player_.AddAnimation(player_idle_animation);
  animation_player_.AddAnimation(player_walk_animation);
}

void Player::HandleInput() {
  const auto& input = game_state_->GetGame().GetInputManager();

  state_ = PlayerState::kIdle;
  direction_ = PlayerDirection::kNone;

  if (input.IsKeyPressed(SDL_SCANCODE_LEFT)) {
    state_ = PlayerState::kWalk;
    direction_ = PlayerDirection::kLeft;
  }

  if (input.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
    state_ = PlayerState::kWalk;
    direction_ = PlayerDirection::kRight;
  }
}

void Player::HandleMovement(const float delta) {
  Vector2f velocity;

  // Move on the x-axis
  if (state_ == PlayerState::kWalk) {
    velocity.x = (direction_ == PlayerDirection::kLeft ? -dx_ : dx_) * delta;
  }

  // Move on the y-axis
  // ...

  // New position
  Vector2f new_pos = GetPosition() + velocity;

  // Check for collisions
  if (new_pos.x < 0) {
    new_pos.x = 0;
  } else if (new_pos.x > 640 - 128) {
    new_pos.x = 640 - 128;
  }

  // Update player position
  SetPosition(new_pos);
}

void Player::HandleAnimation(const float delta) {
  std::string animation;

  switch (state_) {
    case PlayerState::kWalk:
      animation = "player_walk";
      break;
    default:
      animation = "player_idle";
      break;
  }

  animation_player_.SetAnimation(animation);
  animation_player_.Update(delta);

  // TODO: Refactor into animation class?
  const AnimationFrame frame = animation_player_.GetCurrentFrame();
  SetTexture(AssetManager::Instance().GetTexture(frame.texture_id));
  SetTextureRect(SDL_Rect{frame.x, frame.y, frame.width, frame.height});

  // Flip sprite if moving left
  SetFlipped(direction_ == PlayerDirection::kLeft);
}

void Player::Update(const float delta) {
  HandleInput();
  HandleMovement(delta);
  HandleAnimation(delta);
}
