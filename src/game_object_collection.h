#pragma once
#ifndef GAME_OBJECT_COLLECTION_H
#define GAME_OBJECT_COLLECTION_H

#include <memory>
#include <vector>

#include <SDL.h>

#include "game_object.h"

class GameObjectCollection {
 public:
  void Add(std::shared_ptr<GameObject> game_object);

  void Update(const float delta);
  void Render(SDL_Renderer* renderer);

 private:
  std::vector<std::shared_ptr<GameObject>> game_objects_;

  // New objects are initially added to separate array and inserted into the
  // main array at the start of each update. This prevents the update and
  // rendering loops being interrupted.
  std::vector<std::shared_ptr<GameObject>> pending_objects_;
};

#endif
