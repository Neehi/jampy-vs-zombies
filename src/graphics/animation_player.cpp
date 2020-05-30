#include "graphics/animation_player.h"

const std::string& AnimationPlayer::GetCurrentAnimation() const {
  return current_animation_.first;
}

const AnimationFrame& AnimationPlayer::GetCurrentFrame() const {
  return current_animation_.second->GetFrame(current_frame_);
}

void AnimationPlayer::AddAnimation(std::shared_ptr<Animation> animation) {
  animations_.insert(std::make_pair(animation->GetName(), animation));

  if (current_animation_.first.empty()) {
    SetAnimation(animation->GetName());
  }
}

void AnimationPlayer::SetAnimation(const std::string& name) {
  if (current_animation_.first == name) {
    return;
  }

  auto it = animations_.find(name);
  if (it != animations_.end()) {
    current_animation_ = *it;
    current_frame_ = 0;
    current_frame_delta_ = 0;
  }
}

void AnimationPlayer::Update(const float delta) {
  if (animations_.size() == 0) {
    return;
  }

  current_frame_delta_ += delta;
  if (current_frame_delta_ >= current_animation_.second->GetFrameDuration()) {
    current_frame_++;
    if (current_frame_ >= current_animation_.second->GetFrameCount()) {
      current_frame_ = 0;
    }
    current_frame_delta_ = 0;
  }
}
