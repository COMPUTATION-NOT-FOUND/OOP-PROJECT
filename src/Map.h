#pragma once

#include "Game.h"

class Map {
public:
    Map();

    ~Map();

    void LoadMap(int arr[20][20]);

    void DrawMap();

    void Clean();

private:
    SDL_Rect src, dest;
    const char* tex ;

    int map[20][20]{};
};