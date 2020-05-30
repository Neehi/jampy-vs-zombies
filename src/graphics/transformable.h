#ifndef GRAPHICS_TRANSFORMABLE_H_
#define GRAPHICS_TRANSFORMABLE_H_

#include "graphics/transform.h"

class Transformable {
 public:
  Transformable() = default;
  virtual ~Transformable() = default;

  inline Transform& GetTransform() const { return transform_; }

 private:
  mutable Transform transform_{};
};

#endif  // GRAPHICS_TRANSFORMABLE_H_
