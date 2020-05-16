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

void Player::Update(const float delta) {
  // Handle player input
  const auto& input = game_state_->GetGame().GetInputManager();
  Vector2f position = GetPosition();
  std::string animation = "player_idle";
  if (input.IsKeyPressed(SDL_SCANCODE_LEFT)) {
    position.x = std::max((float)0, position.x - dx_ * delta);
    animation = "player_walk";
  }
  if (input.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
    position.x = std::min((float)(640 - 128), position.x + dx_ * delta);
    animation = "player_walk";
  }
  SetPosition(position);

  // Update animation
  animation_player_.SetAnimation(animation);
  animation_player_.Update(delta);
  const AnimationFrame frame = animation_player_.GetCurrentFrame();
  SetTexture(AssetManager::Instance().GetTexture(frame.texture_id));
  SetTextureRect(SDL_Rect{frame.x, frame.y, frame.width, frame.height});
}
