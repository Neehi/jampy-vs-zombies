#ifndef TILEMAP_TILE_SET_H_
#define TILEMAP_TILE_SET_H_

#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

#include <SDL.h>

#include "tilemap/tile.h"

class TileSet {
 public:
  TileSet(const std::string& name,
          const std::string& texture_id,
          const std::size_t tile_width,
          const std::size_t tile_height,
          const std::size_t tile_count,
          const std::size_t cols)
      : name_(name),
        texture_id_(texture_id),
        tile_width_(tile_width),
        tile_height_(tile_height),
        tile_count_(tile_count),
        cols_(cols) {}
  ~TileSet() = default;

  inline const std::string& GetName() const { return name_; }
  inline const std::string& GetTextureId() const { return texture_id_; }
  inline std::size_t GetTileWidth() const { return tile_width_; }
  inline std::size_t GetTileHeight() const { return tile_height_; }
  inline std::size_t GetTileCount() const { return tile_count_; }
  inline std::size_t GetColumnCount() const { return cols_; }
  inline std::size_t GetRowCount() const { return tile_count_ / cols_; }

  const Tile& GetTile(const std::size_t id);

  inline const Tile& GetTile(const std::size_t col,
                             const std::size_t row) {
    return GetTile(row * cols_ + col);
  }

  // Debug

  std::string ToString() const {
    std::stringstream result;
    result << "TileSheet{"
           << "name: \"" << name_ << "\""
           << ", texture_id: \"" << texture_id_ << "\""
           << ", tile_width: " << tile_width_
           << ", tile_height: " << tile_height_
           << ", tile_count: " << tile_count_
           << ", cols: " << cols_
           << ", rows: " << tile_count_ / cols_
           << "}";
    return result.str();
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const TileSet& tile_set) {
    stream << tile_set.ToString();
    return stream;
  }

 private:
  std::string name_;
  std::string texture_id_;
  std::size_t tile_width_;
  std::size_t tile_height_;
  std::size_t tile_count_;
  std::size_t cols_;
  std::unordered_map<std::size_t, Tile> tiles_;
};

#endif  // TILEMAP_TILE_SET_H_
