#include<iostream>
#include<string>

#include <SDL.h>
#include <SDL_image.h>

#include "global.hpp"
#include "texture.hpp" 
#include "role.hpp"

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
        gWindow = SDL_CreateWindow("RoguelikeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

    if (!gRoleTexture.loadFromFile(ROLE_PATH)) {
        std::cout << "Failed to load role texture image!" << std::endl;
        success = false;
    }

    if (!gBGTexture.loadFromFile(BG_PATH)) {
        std::cout << "Failed to load background texture image!" << std::endl;
        success = false;
    }

    return success;
}

void close() {
    // Free loaded images
    gRoleTexture.free();
    gBGTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int gameLoop() {
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

    // The Camera Area
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

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

        // Center the camera over the role
        camera.x = (role.getPosX() + role.roleWidth / 2) - SCREEN_WIDTH / 2;
        camera.y = (role.getPosY() + role.roleHeight / 2) - SCREEN_HEIGHT / 2;

        // Keep the camera in bounds
        if (camera.x < 0) { // Left
            camera.x = 0;
        }
        if (camera.y < 0) { // Top
            camera.y = 0;
        }

        if (camera.x > BG_WIDTH - camera.w) { // Right
            camera.x = BG_WIDTH - camera.w;
        }

        if (camera.y > BG_HEIGHT - camera.h) { // Bottom
            camera.y = BG_HEIGHT - camera.h;
        }


        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gBGTexture.render(0, 0, &camera);

        // render the role in the camera area by subtracting the camera offsets from the role's offsets
        role.render(camera.x, camera.y);

        SDL_RenderPresent(gRenderer);
    }
    close();

    return 0;
}