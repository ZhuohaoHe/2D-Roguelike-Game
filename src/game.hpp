#ifndef GAME_H
#define GAME_H

// Set up SDL and create window
bool init();

// Load media
bool loadMedia();

// Free media and shut down SDL
void close();

int gameLoop();

#endif