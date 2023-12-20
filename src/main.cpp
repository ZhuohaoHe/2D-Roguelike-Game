#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "global.hpp"
#include "game.hpp"

int main(int argc, char* args[]) {
    if (!init()){
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }
    if (!loadMedia()) {
        std::cout << "Failed to load media!" << std::endl;
        return -1;
    } 
    // Main loop flag
    bool quit = false;
    
    // Event handler
    SDL_Event e;

    // Role in the game
    Role role;

    // While application is running
    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // Handle input for the role
            role.handleEvent(e);
        }

        // Move the role
        role.move();

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        role.render();

        SDL_RenderPresent(gRenderer);
    }
    close();

    return 0;
}