#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstddef>
#include <string>

#include <SDL.h>

#include "sprite.h"

class GameObject : public Sprite {
 public:
  GameObject(const std::string texture_id, const float x, const float y,
             const std::size_t width, const std::size_t height);
  GameObject(const std::string texture_id, const std::size_t width,
             const std::size_t height)
      : GameObject(texture_id, 0, 0, width, height) {}
  ~GameObject() = default;

  virtual void Update(const float delta) {}

 private:
  // ...
};

#endif
