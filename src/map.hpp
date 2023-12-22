#ifndef MAP_HPP
#define MAP_HPP

#include "texture.hpp"

// const int TILE_WIDTH = 80;
// const int TILE_HEIGHT = 80;

// Texture gTileTexture;

// class Tile{ 
//     public:
//         Tile(int x, int y, int type);

//         ~Tile();

//         // Render the tile
//         void render(const SDL_Rect& camera);

//         int getType();

//         // Get the collision box
//         SDL_Rect getBox();

//     private:
//         // The attributes of the tile
//         SDL_Rect mBox;

//         // The tile type
//         int mType;
// };

// class Map{

// };

class Background{
    public:
        Background();
        ~Background();

        // Render the background
        void render(int x, int y, SDL_Rect* clip = NULL);

        // load the texture
        bool loadTexture(std::string path);

        void free();

    private:
        Texture gBGTexture;
};

#endif