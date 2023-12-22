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
    if (leftA > rightB || rightA < leftB || topA < bottomB || bottomA > topB) {
        return false;
    }

    return true;
}