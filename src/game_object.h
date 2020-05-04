#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstddef>
#include <memory>

#include <SDL.h>

#include "texture.h"

class GameObject {
 public:
  GameObject() : GameObject(0, 0) {}
  GameObject(float x, float y) : x_(x), y_(y) {}
  ~GameObject() = default;

  virtual void Update() {}
  virtual void Render(SDL_Renderer* sdl_renderer);

  inline float GetX() const { return x_; }
  inline float GetY() const { return y_; }
  inline void SetX(const float x) { x_ = x; }
  inline void SetY(const float y) { y_ = y; }

  void SetTexture(const std::shared_ptr<Texture> texture);

 protected:
  float x_;
  float y_;

 private:
  std::shared_ptr<Texture> texture_{nullptr};
};

#endif
