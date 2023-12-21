#ifndef ROLE_HPP
#define ROLE_HPP

#include <SDL.h>

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
        void render(int camX, int camY);

        int getPosX();
        int getPosY();
    
    private:
        // The X and Y offsets of the role
        int mPosX, mPosY;
        // The velocity of the role
        int mVelX, mVely;
};

#endif