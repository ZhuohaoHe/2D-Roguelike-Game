cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

project(RoguelikeGame)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the path to the installed SDL2 and SDL2_image include directories
set(SDL2_INCLUDE_DIR "/opt/homebrew/include/SDL2")

# Set the path to the installed SDL2 and SDL2_image library directories
set(SDL2_LIB_DIR "/opt/homebrew/lib")

# Include directories for SDL2 and SDL2_image
include_directories(${SDL2_INCLUDE_DIR})

# Link directories for SDL2 and SDL2_image
link_directories(${SDL2_LIB_DIR})

add_executable(RoguelikeGame src/main.cpp src/game.cpp src/global.cpp)

target_link_libraries(RoguelikeGame SDL2 SDL2_image)