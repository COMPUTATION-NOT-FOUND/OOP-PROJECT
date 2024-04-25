#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>


class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    bool running() const { return isRunning; }
    void render();
    void clean();
    static SDL_Renderer *renderer;

private:
    bool isRunning = false;
    SDL_Window *window;

};

