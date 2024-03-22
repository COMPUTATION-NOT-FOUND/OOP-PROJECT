#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    const int FPS=60;
    const int FrameDelay= 1000/60;

    Uint32 framestart;
    int frametime;

    game = new Game();
    game->init("FROG_QUEST", 800, 640, false);

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();

        frametime = SDL_GetTicks() - framestart;
        if(FrameDelay>frametime){

            SDL_Delay(FrameDelay-frametime);

        }
    }

    game->clean();
    delete game;
    return 0;
}