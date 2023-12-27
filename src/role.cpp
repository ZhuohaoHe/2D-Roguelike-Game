#include "global.hpp"
#include "role.hpp"
#include "util.hpp"

Role::Role() {
    // initialize offsets
    mPosX = 0;
    mPosY = SCREEN_HEIGHT - roleHeight + 1;
    
    // initialize collision box dimension
    mCollider.x = mPosX;
    mCollider.y = mPosY;
    mCollider.w = roleWidth;
    mCollider.h = roleHeight;

    // initialize velocity
    mVelX = 0;
    mVely = 0;
}

Role::~Role() {
    roleTexture.free();
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
                jump();
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

    // Update the collision box
    mCollider.x = mPosX;
    mCollider.y = mPosY;
}  

void Role::moveBack() {
    // Move the dot on x axis
    mPosX -= mVelX;

    // Move the dot on y axis
    mPosY -= mVely;

    // Update the collision box
    mCollider.x = mPosX;
    mCollider.y = mPosY;
}

void Role::jump() {
    if (!isJumping) {
        isJumping = true;
        mVely = -JUMP_VEL;
    }
}

void Role::jumpUpdate() {
    // If the role is jumping, apply gravity
    if (isJumping) {
        // Apply gravity
        mVely += GRAVITY;

        // Move the role on the y-axis
        mPosY += mVely;

        // Check if the role has landed on the ground
        if (mPosY + roleHeight >= SCREEN_HEIGHT) {
            mPosY = SCREEN_HEIGHT - roleHeight;
            isJumping = false;
            mVely = 0;  // Stop vertical movement after landing
        }
    }

    mCollider.y = mPosY;
}


void Role::render(int camX, int camY) {
    // Show the dot relative to the camera
    roleTexture.render(mPosX - camX, mPosY - camY);
}

bool Role::loadTexture(std::string path) {
    return roleTexture.loadFromFile(path);
}

SDL_Rect Role::getCollider() {
    return mCollider;
}