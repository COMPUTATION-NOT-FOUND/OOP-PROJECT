#pragma once
#include "Game.h"

class GameObject{
protected:
    int xpos;
    int ypos;
    SDL_Texture* objtexture;
    SDL_Rect srcrect, destrect;
    SDL_Renderer* renderer;

public:
    GameObject(const char* texturesheeet ,int x ,int y);
    ~GameObject();

    virtual void update();
    void Render();
};
class Player: public GameObject{
public:
    int speedx;
    int speedy;
    Player(const char* texturesheeet ,int x ,int y);
    ~Player();

    void update();

};