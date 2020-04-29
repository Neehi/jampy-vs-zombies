cmake_minimum_required(VERSION 3.7)

project(JampyVsZombies)

# Compiler flags
add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# Source files
set (
	SOURCE_FILES
	src/main.cpp
	# ...
)

# Packages
find_package(SDL2 REQUIRED)

# Define include dirs
include_directories(${SDL2_INCLUDE_DIRS})

# Define executable
add_executable(JampyVsZombies ${SOURCE_FILES})

# Define link libraries
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(JampyVsZombies ${SDL2_LIBRARIES})

# Set StartUp Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT JampyVsZombies)
