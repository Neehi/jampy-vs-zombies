#pragma once
#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "graphics/transform.h"

class Transformable {
 public:
  Transformable() = default;
  virtual ~Transformable() = default;

  inline Transform& GetTransform() const { return transform_; }

 private:
  mutable Transform transform_{};
};

#endif
