#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <cstddef>
#include <map>
#include <string>
#include <vector>

struct AnimationFrame {
  std::string texture_id;
  int x;
  int y;
  int width;
  int height;
};

class Animation {
 public:
  explicit Animation(const std::string& name)
      : name_(name), frame_rate_(15), loop_(false) {}
  Animation(const std::string& name,
            const std::vector<AnimationFrame>& frames,
            const float frame_rate,
            const bool loop = true)
      : name_(name), frames_(frames), frame_rate_(frame_rate), loop_(loop) {}

  inline const std::string& GetName() const { return name_; }
  inline std::size_t GetFrameCount() const { return frames_.size(); }
  inline const AnimationFrame& GetFrame(const std::size_t n) const {
    return frames_[n];
  }
  inline float GetFrameRate() const { return frame_rate_; }
  inline float GetFrameDuration() const { return 1.0f / frame_rate_; }
  inline float GetDuration() const { return frames_.size() / frame_rate_; }
  inline bool IsLooped() const { return loop_; }

  inline void AddFrame(const AnimationFrame& frame) {
    frames_.push_back(frame);
  }

 private:
  std::string name_;
  std::vector<AnimationFrame> frames_;
  float frame_rate_;  // frame per second
  bool loop_;
};

#endif
