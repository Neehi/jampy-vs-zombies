#pragma once
#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/vec2.hpp>

#include "transform.h"

class Transformable {
 public:
  Transformable() : transform_() {}
  virtual ~Transformable() = default;

  inline const glm::vec2& GetPosition() const { return transform_.GetPosition(); }
  inline float GetRotation() const { return transform_.GetRotation();  }
  inline float GetScale() const { return transform_.GetScale(); }

  inline void SetPosition(const float x, const float y) { SetPosition(glm::vec2(x, y)); }
  inline void SetPosition(const glm::vec2& position) { transform_.SetPosition(position); }
  inline void SetRotation(const float angle) { transform_.SetRotation(angle); }
  inline void SetScale(const float scale) { transform_.SetScale(scale); }

  inline const Transform& GetTransform() const { return transform_; }

 private:
   Transform transform_;
};

#endif
