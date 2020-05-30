#include "core/game_object_collection.h"

void GameObjectCollection::Add(std::shared_ptr<GameObject> game_object) {
  pending_objects_.push_back(game_object);
}

void GameObjectCollection::Update(const float delta) {
  // Add any pending game objects
  if (pending_objects_.size() > 0) {
    game_objects_.insert(
        game_objects_.end(),
        pending_objects_.begin(),
        pending_objects_.end());
    pending_objects_.clear();
  }

  // Update all game objects
  for (auto& game_object : game_objects_) {
    game_object->Update(delta);
  }
}

void GameObjectCollection::Render(const Renderer& renderer) {
  // Render all game objects
  for (auto& game_object : game_objects_) {
    game_object->Render(renderer);
  }
}
