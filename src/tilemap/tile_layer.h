#pragma once
#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "graphics/renderer.h"
#include "tile.h"
#include "tile_set.h"

// Represents a layer of fixed tiles. These tiles will be rendered as regular
// sprites/textures as no interactions should occur with them - collisions
// will be handled through a separate collision layer. Moveables tile and
// other items will be handled separately as game objects.
class TileLayer {
 public:
  TileLayer(const std::string& name,
            const std::size_t cols,
            const std::size_t rows,
            const std::size_t tile_width,
            const std::size_t tile_height)
      : name_(name),
        cols_(cols),
        rows_(rows),
        tile_width_(tile_width),
        tile_height_(tile_height),
        tile_grid_(rows, std::vector<std::size_t>(cols, 0)) {}
  ~TileLayer() = default;

  inline const std::string& GetName() const { return name_; }
  inline std::size_t GetWidth() const { return cols_ * tile_width_; }
  inline std::size_t GetHeight() const { return rows_ * tile_height_; }

  void AddTileSet(std::shared_ptr<TileSet> tile_set);
  void SetTile(const std::size_t col,
               const std::size_t row,
               const std::size_t tile_id);

  void Render(const Renderer& renderer);

  // Debug

  std::string ToString() const {
    std::stringstream result;
    result << "TileLayer{"
           << "name: \"" << name_ << "\""
           << ", cols: " << cols_
           << ", row: " << rows_
           << ", tile_width: " << tile_width_
           << ", tile_height: " << tile_height_
           << ", tile_set: \"" << tile_set_->GetName() << "\""
           << "}";
    return result.str();
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const TileLayer& tile_layer) {
    stream << tile_layer.ToString();
    return stream;
  }

 private:
  std::string name_;
  std::size_t cols_;
  std::size_t rows_;
  std::size_t tile_width_;
  std::size_t tile_height_;

  // TODO: Update to vector
  std::shared_ptr<TileSet> tile_set_;
  std::vector<std::vector<std::size_t>> tile_grid_;
};

#endif
