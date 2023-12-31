#include "game.hpp"

// TODO: fix the jump bug
// TODO: add animated of the role

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


void close() {
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

    // Main loop flag
    bool quit = false;
    
    // Event handler
    SDL_Event e;


    // Role in the game
    Role role;

    // Load role texture
    if(!role.loadTexture(ROLE_PATH)){
        std::cout << "Failed to load role texture image!" << std::endl;
        return -1;
    }

    // The background
    Background bg;

    // Load background texture
    if(!bg.loadTexture(BG_PATH)){
        std::cout << "Failed to load background texture image!" << std::endl;
        return -1;
    }

    Map map;
    if (!map.loadMapData(MAP_DATA_PATH)) {
        std::cout << "Failed to load map data!" << std::endl;
        return -1;
    }

    if (!map.loadMapTexture(MAP_TEXTURE_PATH)) {
        std::cout << "Failed to load map texture!" << std::endl;
        return -1;
    }




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
        role.jumpUpdate();

        if (handle_collision(role.getCollider(), map.getCollider())) {
            role.moveBack();
        }

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

        // the sequence of rendering is important
        
        // render background
        bg.render(0, 0, &camera);

        map.render(camera);

        // render the role in the camera area by subtracting the camera offsets from the role's offsets
        role.render(camera.x, camera.y);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}