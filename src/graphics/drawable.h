#pragma once
#ifndef DRAWABLE_H
#define DRAWABLE_H

class Renderer;

class Drawable {
 public:
  virtual ~Drawable() = default;

  virtual void Render(const Renderer& renderer) const = 0;
};

#endif
