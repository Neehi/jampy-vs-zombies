# TODO: Check required version
cmake_minimum_required(VERSION 3.7)

project(JampyVsZombies)

# Compiler flags
add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Source files
set(
	SOURCES
	src/main.cpp
	src/player.cpp
	src/player.h
	src/sandbox_state.cpp
	src/sandbox_state.h
)
source_group("" FILES ${SOURCES})

set(
    CORE_SOURCES
    src/core/game_object_collection.cpp
    src/core/game_object_collection.h
    src/core/game_object.cpp
    src/core/game_object.h
    src/core/game_state.cpp
    src/core/game_state.h
    src/core/game_state_manager.cpp
    src/core/game_state_manager.h
    src/core/game.cpp
    src/core/game.h
)
source_group("core" FILES ${CORE_SOURCES})

set(
    GRAPHICS_SOURCES
    src/graphics/animation_player.cpp
    src/graphics/animation_player.h
    src/graphics/animation.h
    src/graphics/drawable.h
    src/graphics/orthographic_camera.cpp
    src/graphics/orthographic_camera.h
    src/graphics/renderer.cpp
    src/graphics/renderer.h
    src/graphics/sprite.cpp
    src/graphics/sprite.h
    src/graphics/transform.h
    src/graphics/transform.inl
    src/graphics/transformable.h
    src/graphics/window.cpp
    src/graphics/window.h
)
source_group("graphics" FILES ${GRAPHICS_SOURCES})

set(
    INPUT_SOURCES
    src/input/input_manager.cpp
    src/input/input_manager.h
)
source_group("input" FILES ${INPUT_SOURCES})

set(
    RESOURCE_SOURCES
    src/resources/asset_manager.cpp
    src/resources/asset_manager.h
)
source_group("resources" FILES ${RESOURCE_SOURCES})

set(
    TILEMAP_SOURCES
    src/tilemap/tile.h
    src/tilemap/tile_layer.cpp
    src/tilemap/tile_layer.h
    src/tilemap/tile_set.cpp
    src/tilemap/tile_set.h
)
source_group("tilemap" FILES ${TILEMAP_SOURCES})

# Packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm CONFIG PATHS "${CMAKE_SOURCE_DIR}/external/glm/cmake/glm/" REQUIRED)

# Define include dirs
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)
if(APPLE)
    include_directories(SYSTEM /usr/local/include/)
endif(APPLE)

# Define executable
add_executable(
    JampyVsZombies
    ${SOURCES}
    ${CORE_SOURCES}
    ${GRAPHICS_SOURCES}
    ${INPUT_SOURCES}
    ${RESOURCE_SOURCES}
    ${TILEMAP_SOURCES}
)

# Define link libraries
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(JampyVsZombies ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# Set StartUp Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT JampyVsZombies)
