#include "TextureManager.h"


 SDL_Texture* TextureManager::LoadTexture(const char* texture,SDL_Renderer* ren){


    SDL_Surface* tempsurface =IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,tempsurface);
    SDL_FreeSurface(tempsurface);
    return tex;
 }
