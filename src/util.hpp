#ifndef UTIL_HPP
#define UTIL_HPP

#include "global.hpp"
#include <SDL.h>
#include <vector>

bool checkCollision(SDL_Rect a, SDL_Rect b);
bool handle_collision(SDL_Rect roleCollider, std::vector<SDL_Rect> mapColiider);

#endif