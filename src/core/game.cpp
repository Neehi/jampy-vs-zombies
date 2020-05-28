#include "game.h"

#include <iostream>

#include <SDL_image.h>

#include "resources/asset_manager.h"

Game::Game(const std::size_t screen_width, const std::size_t screen_height,
           const std::string& title) {
  // Initializing SDL
  std::cout << "Initializing SDL\n";
  if (SDL_Init(0) != 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Initialize SDL_image
  std::cout << "Initializing SDL_image\n";
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "Error initializing SDL_image: " << IMG_GetError() << "\n";
    // TODO: Error handling
  }

  // Create window
  std::cout << "Creating window\n";
  window_ = std::make_unique<Window>(title, screen_width, screen_height);

  // Create SDL renderer
  std::cout << "Creating renderer\n";
  sdl_renderer_ = SDL_CreateRenderer(
      window_->GetSDLWindow(),
      -1,
      SDL_RENDERER_ACCELERATED);

  if (nullptr == sdl_renderer_) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Create input manager
  std::cout << "Creating input manager\n";
  input_manager_ = std::make_unique<InputManager>();

  // Create asset manager
  std::cout << "Creating asset manager\n";
  AssetManager::Instance();  // XXX: Doesn't need to be explicitly called

  // Set game running
  running_ = true;
}

Game::~Game() {
  // Free any resources
  std::cout << "Cleaning up resources\n";
  AssetManager::Instance().Purge();
  // Close window
  std::cout << "Closing window\n";
  SDL_DestroyRenderer(sdl_renderer_);
  window_.reset();
  // Shutdown SDL_image
  std::cout << "Shutting down SDL_image\n";
  IMG_Quit();
  // Shutdown SDL
  std::cout << "Shutting down SDL\n";
  SDL_Quit();
}

void Game::HandleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        std::cout << "Received SDL_Quit event\n";
        running_ = false;
        return;
      default:
        input_manager_->HandleEvent(event);
        break;
    }
  }
}

void Game::Update(const float delta) {
  // Update current game state
  if (current_state_ != nullptr) {
    current_state_->OnUpdate(delta);
  }
}

void Game::Render() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl_renderer_);

  // Render current game state
  if (current_state_ != nullptr) {
    current_state_->OnRender(sdl_renderer_);
  }

  // Update screen
  SDL_RenderPresent(sdl_renderer_);
}

void Game::Run() {
  running_ = true;

  constexpr uint32_t kTicksPerSecond = 1000;
  const uint32_t ticks_per_frame = kTicksPerSecond / frame_rate_;
  const float fixed_delta = 1 / (float)frame_rate_;  // Fixed update delta

  std::cout << "Target FPS: " << frame_rate_ << " (" << ticks_per_frame
            << "ms/frame)\n";

  uint32_t last_ticks = SDL_GetTicks();
  uint32_t current_ticks;
  uint32_t elapsed_ticks;
  uint32_t lag{0};
  uint32_t frames{0};
  uint32_t frame_counter_target{last_ticks + kTicksPerSecond};

  while (running_) {
    // Calculate ticks since last iteration
    current_ticks = SDL_GetTicks();
    elapsed_ticks = current_ticks - last_ticks;
    last_ticks = current_ticks;
    lag += elapsed_ticks;  // Acculumate elapsed ticks

    // Update frame counter
    if (current_ticks >= frame_counter_target) {
      fps_ = frames;
      frames = 0;
      frame_counter_target = current_ticks + kTicksPerSecond;
    }

    // Update logic and render frame
    if (lag >= ticks_per_frame) {
      // Perform fixed update(s)
      while (lag >= ticks_per_frame) {
        HandleEvents();
        Update(fixed_delta);
        lag -= ticks_per_frame;
      }

      // Render a single frame
      Render();
      frames++;

    } else {
      // Sleep for a bit
      SDL_Delay(1);
    }
  }
}

void Game::SetGameState(std::shared_ptr<GameState> state) {
  if (current_state_ != nullptr) {
    if (current_state_->GetID() == state->GetID()) {
      std::cout << "GameState: '" << state->GetID() 
                << "' is already the current state\n";
      return;
    }
    current_state_->OnExit();
  }
  std::cout << "GameState: Setting the current state to '" << state->GetID()
            << "'\n";
  current_state_ = state;
  current_state_->OnEnter();
}
