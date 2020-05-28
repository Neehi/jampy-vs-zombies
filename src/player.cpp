#include "player.h"

#include <glm/vec2.hpp>
#include <SDL.h>

#include "core/game.h"
#include "graphics/window.h"
#include "input/input_manager.h"
#include "resources/asset_manager.h"

constexpr float kOffsetRight{20};
constexpr float kOffsetLeft{-20};
constexpr float kOffsetY{-22};

Player::Player(GameState* game_state, const std::string template_id,
               const std::size_t width, const std::size_t height)
    : GameObject(template_id, width, height),
      game_state_(game_state),
      dx_(60), dy_(0) {
  Window& window = game_state->GetGame().GetWindow();
  GetTransform().SetPosition(
      glm::vec2(
          0 + (float)width_ * 0.5f,
          window.GetHeight() - (float)height_ * 0.5f));
  SetOffset(glm::vec2(kOffsetRight, kOffsetY));
  animation_player_.AddAnimation(player_idle_animation);
  animation_player_.AddAnimation(player_walk_animation);
}

void Player::HandleInput() {
  const InputManager& input = game_state_->GetGame().GetInputManager();

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
  glm::vec2 velocity(0, 0);

  // Move on the x-axis
  if (state_ == PlayerState::kWalk) {
    velocity.x = (direction_ == PlayerDirection::kLeft ? -dx_ : dx_) * delta;
  }

  // Move on the y-axis
  // ...

  // New position
  glm::vec2 new_pos = GetTransform().GetPosition() + velocity;

  // Check for collisions
  const float x1 = width_ * 0.5f;
  const float y1 = height_ * 0.5f;
  const float x2 = 640 - width_ * 0.5f;
  const float y2 = 640 - height_ * 0.5f;
  if (new_pos.x < x1) {
    new_pos.x = x1;
  } else if (new_pos.x > x2) {
    new_pos.x = x2;
  }

  // Update player position
  GetTransform().SetPosition(new_pos);
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

  // Set offset based on direction
  SetOffset(glm::vec2{
      direction_ == PlayerDirection::kLeft ? kOffsetLeft : kOffsetRight,
      kOffsetY});
}

void Player::Update(const float delta) {
  HandleInput();
  HandleMovement(delta);
  HandleAnimation(delta);
}

void Player::Render(SDL_Renderer* renderer) const {
  Sprite::Render(renderer);

  // Debug...
  const glm::vec2 position =  GetTransform().GetPosition();
  const SDL_Rect hit_rect{
      static_cast<int>(position.x - (float)width_ * 0.5f),
      static_cast<int>(position.y - (float)height_ * 0.5f),
      width_,
      height_};
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &hit_rect);
}
