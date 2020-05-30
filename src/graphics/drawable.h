#ifndef GRAPHICS_DRAWABLE_H_
#define GRAPHICS_DRAWABLE_H_

class Renderer;

class Drawable {
 public:
  virtual ~Drawable() = default;

  virtual void Render(const Renderer& renderer) const = 0;
};

#endif  // GRAPHICS_DRAWABLE_H_
