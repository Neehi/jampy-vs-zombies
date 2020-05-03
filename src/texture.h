#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstddef>
#include <string>

#include <SDL.h>

class Texture {
 public:
  Texture(const std::string path, SDL_Renderer* sdl_renderer);
  ~Texture();

  void Render(SDL_Renderer* sdl_renderer,
              const SDL_Rect* dst_rect) const;
  void Render(SDL_Renderer* sdl_renderer,
              const SDL_Rect* src_rect,
              const SDL_Rect* dst_rect) const;

  inline std::size_t GetWidth() const { return width_; }
  inline std::size_t GetHeight() const { return height_; }

  inline SDL_Texture* GetSDLTexture() const { return sdl_texture_; }

 private:
  SDL_Texture* sdl_texture_;
  std::size_t width_;
  std::size_t height_;
};

#endif
