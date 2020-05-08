#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstddef>
#include <string>

#include <SDL.h>

class GameObject {
 public:
  GameObject(const std::string texture_id, const float x, const float y,
             const std::size_t width, const std::size_t height);
  GameObject(const std::string texture_id, const std::size_t width,
             const std::size_t height)
      : GameObject(texture_id, 0, 0, width, height) {}
  ~GameObject() = default;

  virtual void Update(const float delta) {}
  virtual void Render(SDL_Renderer* renderer);

  inline float GetX() const { return x_; }
  inline float GetY() const { return y_; }
  inline void SetX(const float x) { x_ = x; }
  inline void SetY(const float y) { y_ = y; }

  inline std::size_t GetWidth() const { return width_; }
  inline std::size_t GetHeight() const { return height_; }

  void SetTexture(const std::string texture_id);
  inline void SetClipX(const std::size_t clip_x) { clip_x_ = clip_x; }
  inline void SetClipY(const std::size_t clip_y) { clip_y_ = clip_y; }

 protected:
  float x_;
  float y_;

 private:
  SDL_Texture* texture_{nullptr};
  std::size_t clip_x_{0};
  std::size_t clip_y_{0};
  std::size_t width_;
  std::size_t height_;
};

#endif
