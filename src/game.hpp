#ifndef GAME_H
#define GAME_H

#include "global.hpp"
#include "texture.hpp" 
#include "role.hpp"
#include "map.hpp"
#include "util.hpp"

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

// Set up SDL and create window
bool init();

// Free media and shut down SDL
void close();

int gameLoop();

#endif