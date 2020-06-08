# Jampy vs Zombies

A simple 2D platformer built with SDL2 for the [Udacity C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

## Platforms

The following platforms are supported:
* Windows: Tested on Windows 10 Professional 64-bit
* Mac OS X: Tested on macOS Catalina 10.15.3
* Linux: Currently untested

## Tools Required

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Library Dependencies

* SDL2 >= 2.0
  * All OSes: [click here for installation instructions](https://wiki.libsdl.org/Installation)
  * Linux: an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image >= 2.0
* GLM (located in external)

## Basic Build Instructions

1. Clone this repo
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./JampyVsZombies`
