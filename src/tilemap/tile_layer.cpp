#include "tile_layer.h"

#include <glm/vec2.hpp>

#include "graphics/sprite.h"
#include "resources/asset_manager.h"

void TileLayer::AddTileSet(std::shared_ptr<TileSet> tile_set) {
  tile_set_ = tile_set;
}

void TileLayer::SetTile(const std::size_t col,
                        const std::size_t row,
                        const std::size_t tile_id) {
  if (row > rows_ || col > cols_) {
    return;
  }

  tile_grid_[row][col] = tile_id;
}

void TileLayer::Render(SDL_Renderer* renderer) {
  std::size_t tile_id;
  glm::vec2 position;

  for (std::size_t j = 0; j < rows_; j++) {
    position.y = (float)(j * tile_height_);

    for (std::size_t i = 0; i < cols_; i++) {
      tile_id = tile_grid_[j][i];

      if (tile_id == 0) {
        continue;
      }

      const Tile tile = tile_set_->GetTile(tile_id - 1);
      Sprite sprite(
          AssetManager::Instance().GetTexture(tile.texture_id),
          tile.src_rect
      );
      sprite.SetCentered(false);

      position.x = (float)(i * tile_width_);
      sprite.SetPosition(position);

      sprite.Render(renderer);
    }
  }
}
