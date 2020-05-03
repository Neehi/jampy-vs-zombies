#include "texture.h"

#include <iostream>

#include <SDL_image.h>

Texture::Texture(const std::string path, SDL_Renderer* sdl_renderer) {
  std::cout << "Loading image from '" << path << "'\n";
  SDL_Surface* sdl_surface = IMG_Load(path.c_str());

  if (NULL == sdl_surface) {
    std::cout << "Error loading texture: " << IMG_GetError() << "\n";
    // TODO: Error handling
    return;
  }

  std::cout << "Creating " << sdl_surface->w << "x" << sdl_surface->h
            << " texture from '" << path << "'\n";
  sdl_texture_ = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);

  width_ = sdl_surface->w;
  height_ = sdl_surface->h;

  SDL_FreeSurface(sdl_surface);

  if (NULL == sdl_texture_) {
    std::cout << "Error creating texture: " << IMG_GetError() << "\n";
    // TODO: Error handling
  }
}

Texture::~Texture() {
  if (nullptr != sdl_texture_) {
    std::cout << "Destroying SDL texture\n";
    SDL_DestroyTexture(sdl_texture_);
  }
}

void Texture::Render(SDL_Renderer* sdl_renderer, 
                     const SDL_Rect* dst_rect) const {
  Texture::Render(sdl_renderer, NULL, dst_rect);
}

void Texture::Render(SDL_Renderer* sdl_renderer,
                     const SDL_Rect* src_rect,
                     const SDL_Rect* dst_rect) const {
  SDL_RenderCopy(sdl_renderer, sdl_texture_, src_rect, dst_rect);
}
