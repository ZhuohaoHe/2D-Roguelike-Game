#include "global.hpp"
#include "role.hpp"
#include "texture.hpp"

Role::Role() {
    // initialize offsets
    mPosX = 0;
    mPosY = 0;

    // initialize velocity
    mVelX = 0;
    mVely = 0;
}

int Role::getPosX() {
    return mPosX;
}

int Role::getPosY() {
    return mPosY;
}

void Role::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVely -= velocity;
                break;
            case SDLK_DOWN:
                mVely += velocity;
                break;
            case SDLK_LEFT:
                mVelX -= velocity;
                break;
            case SDLK_RIGHT:
                mVelX += velocity;
                break;
        }
    } 
    // If a key was released, adjust the role's velocity to stop moving
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVely += velocity;
                break;
            case SDLK_DOWN:
                mVely -= velocity;
                break;
            case SDLK_LEFT:
                mVelX += velocity;
                break;
            case SDLK_RIGHT:
                mVelX -= velocity;
                break;
        }
    }
}

void Role::move() {
    // Move the dot on x axis
    mPosX += mVelX;

    // Move the dot on y axis
    mPosY += mVely;

    // If the dot went too far to out of the range of the screen
    if ((mPosX < 0) || (mPosX + roleWidth > BG_WIDTH)) {
        // Move back
        mPosX -= mVelX;
    }

    if ((mPosY < 0) || (mPosY + roleHeight > BG_HEIGHT)) {
        // Move back
        mPosY -= mVely;
    }   
}

void Role::render(int camX, int camY) {
    // Show the dot relative to the camera
    gRoleTexture.render(mPosX - camX, mPosY - camY);
}