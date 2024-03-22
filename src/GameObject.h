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
    Player(const char* texturesheeet ,int x ,int y);
    ~Player();

    void update(int x, int y);

};