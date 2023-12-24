#include "map.hpp"
#include <iostream>

Tile::Tile(int x, int y, int type) {
    // Get the offsets
    mBox.x = x;
    mBox.y = y;

    // Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    // Get the tile type
    mType = type;
}

int Tile::getType() {
    return mType;
}

SDL_Rect Tile::getBox() {
    return mBox;
}

Map::Map() {}

Map::~Map() {
    for (int i = 0; i < TOTAL_TILES; i ++) {
        delete tiles[i];
    }
    mapTexture.free();
}

void Map::linkTiles() {
    tileClips[ 0 ].x = 0;
    tileClips[ 0 ].y = 0;
    tileClips[ 0 ].w = TILE_WIDTH;
    tileClips[ 0 ].h = TILE_HEIGHT;

    tileClips[ 1 ].x = 0;
    tileClips[ 1 ].y = 80;
    tileClips[ 1 ].w = TILE_WIDTH;
    tileClips[ 1 ].h = TILE_HEIGHT;
}

bool Map::loadMapData(std::string path) {
    // The tile offsets
    int x = 0, y = 0;

    // Open the map data
    std::ifstream map_data(path);

    // If the map couldn't be loaded
    if (!map_data.is_open()) {
        printf("Unable to load map file!\n");
        return false;
    } else {
        for (int i = 0; i < TOTAL_TILES; i ++) {
            // Determine what kind of tile will be made
            int tileType = -1;

            // Read tile from map file
            map_data >> tileType;

            // If the was a problem in reading the map
            if (map_data.fail()) {
                // Stop loading map
                printf("Error loading map: Unexpected end of file!\n");
                map_data.close();
                return false;
            }

            // If the number is a valid tile number
            if ((tileType >= 0) && (tileType < TOTLE_TILE_SPRITES)) {
                tiles[i] = new Tile(x, y, tileType);
            } else {
                // Stop loading map
                printf("Error loading map: Invalid tile type at %d!\n", i);
                map_data.close();
                return false;
            }

            // Move to next tile spot
            x += TILE_WIDTH;

            // If we've gone too far
            if (x >= BG_WIDTH) {
                // Move back
                x = 0;

                // Move to the next row
                y += TILE_HEIGHT;
            }
        }
        // Link the tiles
        linkTiles();
    }
    // Close the file
    map_data.close();
    return true;
}

bool Map::loadMapTexture(std::string path) {
    return mapTexture.loadFromFile(path);
}



void Map::render(const SDL_Rect& camera) {
    // If the tile is on screen
    for (int i = 0; i < TOTAL_TILES; i ++) {
        SDL_Rect tileBox = tiles[i]->getBox();
        if (checkCollision(camera, tileBox)) {
            // Show the tile
            mapTexture.render(tileBox.x - camera.x, tileBox.y - camera.y, &tileClips[tiles[i]->getType()]);
        }
    }
}



Background::Background() { }

Background::~Background() {
    bgTexture.free();
}

bool Background::loadTexture(std::string path) {
    return bgTexture.loadFromFile(path);
}

void Background::render(int x, int y, SDL_Rect* clip) {
    bgTexture.render(x, y, clip);
}

