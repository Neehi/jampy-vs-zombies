#ifndef GRAPHICS_ANIMATION_PLAYER_H_
#define GRAPHICS_ANIMATION_PLAYER_H_

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "graphics/animation.h"

using AnimationMap = std::map<std::string, std::shared_ptr<Animation>>;

class AnimationPlayer {
 public:
  AnimationPlayer() : current_animation_() {}
  ~AnimationPlayer() = default;

  const std::string& GetCurrentAnimation() const;
  const AnimationFrame& GetCurrentFrame() const;

  void SetAnimation(const std::string& name);

  void AddAnimation(std::shared_ptr<Animation> animation);

  void Update(float delta);

 private:
  AnimationMap animations_;
  std::pair<std::string, std::shared_ptr<Animation>> current_animation_;
  std::size_t current_frame_{0};
  float current_frame_delta_{0};
};

#endif  // GRAPHICS_ANIMATION_PLAYER_H_
