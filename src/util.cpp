#include "util.hpp"

bool checkCollision(SDL_Rect a, SDL_Rect b) {

    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Define the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Define the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (leftA >= rightB || rightA <= leftB || topA >= bottomB || bottomA <= topB) {
        return false;
    }
    return true;
}

bool handle_collision(SDL_Rect roleCollider, std::vector<SDL_Rect> mapCollider) {
    // Go through the tiles
    for (int i = 0; i < mapCollider.size(); i ++) {
        // If the tile is a wall type tile
        if (checkCollision(roleCollider, mapCollider[i])) {
            // Move back
            return true;
        }
    }
    return false;
}