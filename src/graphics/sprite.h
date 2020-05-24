#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include <glm/vec2.hpp>
#include <SDL.h>

#include "graphics/drawable.h"
#include "graphics/transformable.h"

class Sprite : public Drawable, public Transformable {
 public:
  Sprite() : texture_(NULL), src_rect_() {}
  Sprite(SDL_Texture* texture) : texture_(texture), src_rect_() {}
  Sprite(SDL_Texture* texture, const SDL_Rect& src_rect)
      : texture_(texture), src_rect_(src_rect) {}
  ~Sprite() = default;

  inline const SDL_Texture* GetTexture() const { return texture_; }
  inline const SDL_Rect& GetTextureRect() const { return src_rect_; }
  inline int GetWidth() const { return src_rect_.w; }
  inline int GetHeight() const { return src_rect_.h; }
  inline const SDL_Rect& GetBounds() const {
    return SDL_Rect{0, 0, src_rect_.w, src_rect_.h};
  }
  inline const glm::vec2& GetOffset() const { return offset_; }
  inline bool IsCentered() const { return centered_; }
  inline bool IsFlipped() const { return flip_; }

  inline void SetTexture(SDL_Texture* texture) { texture_ = texture; }
  inline void SetTextureRect(const SDL_Rect& src_rect) { src_rect_ = src_rect; }
  inline void SetOffset(const glm::vec2& offset) { offset_ = offset; }
  inline void SetCentered(const bool center) { centered_ = center; }
  inline void SetFlipped(const bool flip) { flip_ = flip; }

  virtual void Render(SDL_Renderer* renderer) const override;

 private:
  SDL_Texture* texture_;
  SDL_Rect src_rect_;
  glm::vec2 offset_{0, 0};
  bool centered_{true};
  bool flip_{false};
};

#endif
