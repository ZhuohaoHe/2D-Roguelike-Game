#ifndef ROLE_HPP
#define ROLE_HPP

#include "texture.hpp"

#include <vector>
#include <SDL.h>

const int ROLE_WIDTH = 32;
const int ROLE_HEIGHT = 32;

// Role in the game
class Role{
    public:
        int roleWidth = ROLE_WIDTH;
        int roleHeight = ROLE_HEIGHT;

        // move velocity
        int velocity = 10;

        Role();

        ~Role();

        // Takes key presses and adjusts the role's direction
        void handleEvent(SDL_Event& e);

        // Move the role
        void move();

        // Render the role on the screen
        void render(int camX, int camY);

        int getPosX();
        int getPosY();

        // load the texture
        bool loadTexture(std::string path);

        void free();
    
    private:

        Texture roleTexture;

        // The X and Y offsets of the role
        int mPosX, mPosY;
        // The velocity of the role
        int mVelX, mVely;

        // The role's collision box
        SDL_Rect mCollider;
};

#endif