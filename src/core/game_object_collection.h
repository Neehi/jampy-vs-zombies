#ifndef CORE_GAME_OBJECT_COLLECTION_H_
#define CORE_GAME_OBJECT_COLLECTION_H_

#include <memory>
#include <vector>

#include "core/game_object.h"
#include "graphics/renderer.h"

class GameObjectCollection {
 public:
  void Add(std::shared_ptr<GameObject> game_object);

  void Update(const float delta);
  void Render(const Renderer& renderer);

 private:
  std::vector<std::shared_ptr<GameObject>> game_objects_;

  // New objects are initially added to separate array and inserted into the
  // main array at the start of each update. This prevents the update and
  // rendering loops being interrupted.
  std::vector<std::shared_ptr<GameObject>> pending_objects_;
};

#endif  // CORE_GAME_OBJECT_COLLECTION_H_
