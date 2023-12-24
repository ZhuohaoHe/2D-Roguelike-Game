#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <SDL.h>
#include <SDL_image.h>

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

#endif