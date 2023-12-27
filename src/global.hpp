#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SDL.h>
#include <string>

const std::string BG_PATH = "../assets/pic/bg.png";
const std::string ROLE_PATH = "../assets/pic/role.png";
const std::string MAP_TEXTURE_PATH = "../assets/pic/tiles.png";
const std::string MAP_DATA_PATH = "../assets/map/map.map";

const int TOTAL_TILES = 512;

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

const int BG_WIDTH = 1024;
const int BG_HEIGHT = 512;

extern SDL_Renderer* gRenderer;

extern SDL_Window* gWindow;

#endif