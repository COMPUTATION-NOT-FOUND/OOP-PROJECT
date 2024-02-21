#pragma once
#include "Game.h"

class GameObject{
int xpos;
int ypos;
SDL_Texture* objtexture;
SDL_Rect srcrect, destrect;
SDL_Renderer* renderer;



public:
    GameObject(const char* texturesheeet ,SDL_Renderer* ren,int ,int y);
    ~GameObject();

    void update();
    void Render();


};