#include "tile_set.h"

const Tile& TileSet::GetTile(const std::size_t id) {
  // XXX: Might be more efficient just to store the tiles
  //      when the tile sheet is instantiated
  auto it = tiles_.find(id);
  if (it == tiles_.end()) {
    Tile tile = {texture_id_,
                 SDL_Rect{static_cast<int>((id % cols_) * tile_width_),
                          static_cast<int>((id / cols_) * tile_height_),
                          static_cast<int>(tile_width_),
                          static_cast<int>(tile_height_)}};
    it = tiles_.insert(std::make_pair(id, tile)).first;
  }
  return it->second;
}
