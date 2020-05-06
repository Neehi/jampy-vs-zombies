#include "game.h"

#include <iostream>

#include <SDL_image.h>

Game::Game(const std::size_t screen_width, const std::size_t screen_height,
           const std::string& title)
    : screen_width_(screen_width), screen_height_(screen_height) {
  // Initializing SDL
  std::cout << "Initializing SDL\n";
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Initialize SDL_image
  std::cout << "Initializing SDL_image\n";
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "Error initializing SDL_image: " << IMG_GetError() << "\n";
    // TODO: Error handling
  }

  // Create SDL window
  std::cout << "Creating window (" << screen_width << "x" << screen_height
            << ")\n";
  sdl_window_ = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      static_cast<int>(screen_width),
      static_cast<int>(screen_height),
      SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_) {
    std::cerr << "Error creating window: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Create SDL renderer
  std::cout << "Creating renderer\n";
  sdl_renderer_ = SDL_CreateRenderer(
      sdl_window_,
      -1,
      SDL_RENDERER_ACCELERATED);

  if (nullptr == sdl_renderer_) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
    // TODO: Error handling
  }

  // Create input manager
  std::cout << "Creating input manager\n";
  input_manager_ = std::make_unique<InputManager>();

  // Set game running
  running_ = true;
}

Game::~Game() {
  // Shutdown SDL_image
  std::cout << "Shutting down SDL_image\n";
  IMG_Quit();
  // Shutdown SDL
  std::cout << "Shutting down SDL\n";
  SDL_DestroyRenderer(sdl_renderer_);
  SDL_DestroyWindow(sdl_window_);
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
      std::cout << "FPS: " << frames << "\n";
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
