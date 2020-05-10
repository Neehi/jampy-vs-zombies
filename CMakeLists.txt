cmake_minimum_required(VERSION 3.7)

project(JampyVsZombies)

# Compiler flags
add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Source files
set (
	SOURCE_FILES
	src/asset_manager.cpp
	src/asset_manager.h
	src/drawable.h
	src/game.cpp
	src/game.h
	src/game_object.cpp
	src/game_object.h
	src/game_state.cpp
	src/game_state.h
	src/input_manager.cpp
	src/input_manager.h
	src/main.cpp
	src/player.cpp
	src/player.h
	src/sprite.cpp
	src/sprite.h
	src/transform.h
	src/transformable.h
	src/vector2.h
)

# Packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Define include dirs
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Define executable
add_executable(JampyVsZombies ${SOURCE_FILES})

# Define link libraries
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(JampyVsZombies ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# Set StartUp Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT JampyVsZombies)
