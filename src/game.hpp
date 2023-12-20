#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<string>

#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Texture {
    public:
        Texture();
        ~Texture();

        // Load image at specified path
        bool loadFromFile(std::string path);

        // Deallocate texture
        void free();

        // Render texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL);

        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
};

// Role in the game
class Role{
    public:
        int roleWidth = 20;
        int roleHeight = 20;

        // move velocity
        int velocity = 10;

        Role();

        // Takes key presses and adjusts the role's direction
        void handleEvent(SDL_Event& e);

        // Move the role
        void move();

        // Render the role on the screen
        void render();
    
    private:
        // The X and Y offsets of the role
        int mPosX, mPosY;
        // The velocity of the role
        int mVelX, mVely;
};

// Set up SDL and create window
bool init();

// Load media
bool loadMedia();

// Free media and shut down SDL
void close();

#endif