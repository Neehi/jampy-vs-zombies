#pragma once
#ifndef TILE_H
#define TILE_H

#include <ostream>
#include <sstream>
#include <string>

#include <SDL.h>

struct Tile {
  std::string texture_id;
  SDL_Rect src_rect;

  // Debug

  std::string ToString() const {
    std::stringstream result;
    result << "Tile{"
           << "texture_id: \"" << texture_id << "\""
           << ", x: " << src_rect.x
           << ", y: " << src_rect.y
           << ", w: " << src_rect.w
           << ", h: " << src_rect.w
           << "}";
    return result.str();
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const Tile& tile) {
    stream << tile.ToString();
    return stream;
  }
};

#endif
