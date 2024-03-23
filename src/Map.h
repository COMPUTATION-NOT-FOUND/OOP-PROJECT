#pragma once
#include "Game.h"

class Map{
public:
     Map();
     ~Map();

     void LoadMap(int arr[20][20]);
     void DrawMap();

private:
    SDL_Rect src,dest;
    SDL_Texture* tex;

    int map [20][20]{};
};
