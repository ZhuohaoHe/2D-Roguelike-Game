#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "global.hpp"
#include "texture.hpp"

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

Texture gBGTexture;

Texture gRoleTexture;