#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include "global.hpp"
#include "texture.hpp"
#include "util.hpp"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
const int TOTLE_TILE_SPRITES = 4;
const int TOTAL_TILES = 256;



class Tile{ 
    public:
        Tile(int x, int y, int type);

        int getType();

        // Get the collision box
        SDL_Rect getBox();

    private:

        // The attributes of the tile
        SDL_Rect mBox;

        // The tile type
        int mType;
};

class Map{
    public:
        Map();

        ~Map();

        // Load the map data
        bool loadMapData(std::string path);

        // Load the map texture
        bool loadMapTexture(std::string path);

        // Render the map
        void render(const SDL_Rect& camera);

        void linkTiles();

    private:
        // Tiles in map
        Tile* tiles[TOTAL_TILES];

        Texture mapTexture;

        // Tile clips
        SDL_Rect tileClips[TOTLE_TILE_SPRITES];
};

class Background{
    public:
        Background();
        ~Background();

        // Render the background
        void render(int x, int y, SDL_Rect* clip = NULL);

        // load the texture
        bool loadTexture(std::string path);

    private:
        Texture bgTexture;
};

#endif