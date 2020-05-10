#pragma once
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL.h>

class Drawable {
 public:
  virtual ~Drawable() = default;

  virtual void Render(SDL_Renderer* renderer) const = 0;
};

#endif
