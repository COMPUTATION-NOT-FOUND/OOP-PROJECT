#pragma once
#include "Game.h"

class GameObject{
protected:
    int xpos;
    int ypos;
    SDL_Texture* objtexture;
    SDL_Rect destrect;


public:
    GameObject(int size ,int x ,int y);
    ~GameObject();

    virtual void update() =0;
    virtual void Render() =0;
    SDL_Rect GetDestrect();
};
class Player: public GameObject{
public:
    int speedx;
    int speedy;
    std:: string frame;
    std:: string texturesheet;
    std:: string type;
    Player(const char* texturesheeet,int size ,int x ,int y,const char* frame,const char* type );
    ~Player();

    void update();

    void Render();

};

class Fruit: public GameObject{

public:
    Player*player;
    Fruit(const char* texturesheeet ,int size ,int x ,int y,Player * p);
    ~Fruit();
    void update();
    void Render();
    bool IsInteresct();

};