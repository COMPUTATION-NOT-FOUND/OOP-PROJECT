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
    virtual void Render();
};
class Player: public GameObject{
public:
    int speedx;
    int speedy;
    std:: string frame;
    std:: string texturesheet;
    std:: string type;
    Player(const char* texturesheeet ,int x ,int y,const char* frame,const char* type );
    ~Player();

    void update();

    void Render();

};