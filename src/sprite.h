#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>

#include "drawable.h"
#include "transformable.h"

class Sprite : public Drawable, public Transformable {
 public:
  Sprite() : texture_(NULL), src_rect_() {}
  Sprite(SDL_Texture* texture) : texture_(texture), src_rect_() {}
  Sprite(SDL_Texture* texture, const SDL_Rect& src_rect)
      : texture_(texture), src_rect_(src_rect) {}
  ~Sprite() = default;

  const SDL_Texture* GetTexture() const { return texture_; }
  const SDL_Rect& GetTextureRect() const { return src_rect_; }
  int GetWidth() const { return src_rect_.w; }
  int GetHeight() const { return src_rect_.h; }

  const SDL_Rect& GetBounds() const {
    return SDL_Rect{0, 0, src_rect_.w, src_rect_.h};
  }

  inline void SetTexture(SDL_Texture* texture) { texture_ = texture; }
  inline void SetTextureRect(const SDL_Rect& src_rect) { src_rect_ = src_rect; }

  virtual void Render(SDL_Renderer* renderer) const override;

 private:
  SDL_Texture* texture_;
  SDL_Rect src_rect_;
};

#endif
