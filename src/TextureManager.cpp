#include "TextureManager.h"
std::map<std::string, SDL_Texture*> TextureManager::textures;
SDL_Texture *TextureManager::LoadTexture(const char *filename) {
    SDL_Surface *temp = IMG_Load(filename);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, temp);
    if (texture == nullptr) {
        cout << "Could not load " << filename << endl;
    }
    else{
        textures[filename]=texture;
    }
    SDL_FreeSurface(temp);
    return texture;
}

void TextureManager::Draw(std::string filename, SDL_Rect *src, SDL_Rect *dest) {

    SDL_RenderCopy(Game::renderer, textures[filename], src, dest);
}

TextureManager::~TextureManager(){
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}