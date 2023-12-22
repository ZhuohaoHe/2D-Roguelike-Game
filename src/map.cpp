#include "map.hpp"
// #include "util.hpp"

// Tile::Tile(int x, int y, int type) {
//     // Get the offsets
//     mBox.x = x;
//     mBox.y = y;

//     // Set the collision box
//     mBox.w = TILE_WIDTH;
//     mBox.h = TILE_HEIGHT;

//     // Get the tile type
//     mType = type;
// }

// void Tile::render(const SDL_Rect& camera) {
//     // If the tile is on screen
//     if (checkCollision(camera, mBox)) {
//         // Show the tile
//         gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &tileClips[mType]);
//     }
// }
Background::Background() { }

Background::~Background() {
    gBGTexture.free();
}

bool Background::loadTexture(std::string path) {
    return gBGTexture.loadFromFile(path);
}

void Background::render(int x, int y, SDL_Rect* clip) {
    gBGTexture.render(x, y, clip);
}

