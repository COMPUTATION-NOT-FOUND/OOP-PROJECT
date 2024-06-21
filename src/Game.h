#ifndef GAME_PROJ_GAME_H
#define GAME_PROJ_GAME_H

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

using namespace std;

class Game {
public:
    Game();

    ~Game();

    void init(const char *title, int w, int h, bool fullscreen);

    void handleEvents();

    void update();

    void render() const;

    void clean();

    void reset();

    bool running() const { return isRunning; }

    bool showStart = true;
    bool showEnd = false;
    bool showGame = false;
    static SDL_Renderer *renderer;

private:
    int count = 0;
    bool isRunning{};
    SDL_Window *window{};
};

#endif //GAME_PROJ_GAME_H
