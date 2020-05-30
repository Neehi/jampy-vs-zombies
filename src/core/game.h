#ifndef CORE_GAME_H_
#define CORE_GAME_H_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "core/game_state.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "input/input_manager.h"

class Game {
  static const uint32_t kDefaultFrameRate = 60;

 public:
  Game(const std::size_t screen_width, const std::size_t screen_height,
       const std::string& title);
  ~Game();

  void Run();

  void SetGameState(std::shared_ptr<GameState> state);

  inline Window& GetWindow() const { return *window_; }
  inline Renderer& GetRenderer() const { return *renderer_; }

  inline std::uint32_t GetFPS() const { return fps_; }

  inline InputManager& GetInputManager() const { return *input_manager_; }

 protected:
  void HandleEvents();
  void Update(const float delta);
  void Render();

 private:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

 private:
  std::unique_ptr<Window> window_;
  std::unique_ptr<Renderer> renderer_;

  uint32_t frame_rate_{kDefaultFrameRate};
  uint32_t fps_{0};

  std::unique_ptr<InputManager> input_manager_;

  bool running_{false};

  std::shared_ptr<GameState> current_state_{nullptr};
};

#endif  // CORE_GAME_H_
