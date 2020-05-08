#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstddef>
#include <string>

#include <SDL.h>

class GameObject {
 public:
  GameObject() : GameObject(0, 0) {}
  GameObject(float x, float y) : x_(x), y_(y) {}
  ~GameObject() = default;

  virtual void Update(const float delta) {}
  virtual void Render(SDL_Renderer* sdl_renderer);

  inline float GetX() const { return x_; }
  inline float GetY() const { return y_; }
  inline void SetX(const float x) { x_ = x; }
  inline void SetY(const float y) { y_ = y; }

  void SetTexture(std::string id);

 protected:
  float x_;
  float y_;

 private:
  SDL_Texture* texture_{NULL};
};

#endif
