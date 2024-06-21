#pragma once

#include "Game.h"
#include <map>



class TextureManager {
private:
    static std::map<std::string, SDL_Texture*> textures;
public:
    static SDL_Texture *LoadTexture(const char *filename);

    static void Draw(std::string filename, SDL_Rect *src, SDL_Rect *dest);

    ~TextureManager();
};
