#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <SDL.h>

const std::string BG_PATH = "../res/pic/bg.png";
const std::string ROLE_PATH = "../res/pic/dot.bmp";

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

extern Texture gBGTexture;

extern Texture gRoleTexture;

#endif