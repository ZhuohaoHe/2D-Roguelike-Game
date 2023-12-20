#include<iostream>
#include<string>

#include <SDL.h>
#include <SDL_image.h>

#include "global.hpp"
#include "game.hpp"

Texture gRoleTexture;

Texture::Texture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(std::string path) {
    // Get rid of preexisting texture
    free();

    SDL_Texture* newTexture = NULL;

    // load image
    SDL_Surface* loadSurface = IMG_Load(path.c_str());

    if(loadSurface == NULL) {
        std::cout <<  "Unable to load image %s! SDL_image Error: %s\n" << path.c_str() << IMG_GetError() << std::endl;
    } else {
        // Color key image
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);

        if (newTexture == NULL) {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
        } else {
            // set image dimensions to Texture
            mWidth = loadSurface->w;
            mHeight = loadSurface->h;
        }

        // delete old surface
        SDL_FreeSurface(loadSurface);
    }
    // assign new texture to mTexture
    mTexture = newTexture;
    return mTexture != NULL;
}

void Texture::free() {
    // Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect* clip) {
    // Set rendering space 
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // set clip 
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}   

Role::Role() {
    // initialize offsets
    mPosX = 0;
    mPosY = 0;

    // initialize velocity
    mVelX = 0;
    mVely = 0;
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
    if ((mPosX < 0) || (mPosX + roleWidth > SCREEN_WIDTH)) {
        // Move back
        mPosX -= mVelX;
    }

    if ((mPosY < 0) || (mPosY + roleHeight > SCREEN_HEIGHT)) {
        // Move back
        mPosY -= mVely;
    }   
}

void Role::render() {
    gRoleTexture.render(mPosX, mPosY);
}

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError() << std::endl;
		success = false;
    } else {
        // set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Create Windows
        gWindow = SDL_CreateWindow("RougelikeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
            success = false;
        } else {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (gRenderer == NULL) {
                std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
                success = false;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Init Image Loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    return success;
}


bool loadMedia() {
    bool success = true;

    if (!gRoleTexture.loadFromFile("../res/pic/dot.bmp")) {
        std::cout << "Failed to load role texture image!" << std::endl;
        success = false;
    }

    return success;
}

void close() {
    // Free loaded images
    gRoleTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}