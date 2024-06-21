#define SDL_MAIN_HANDLED

#include "Game.h"

using namespace std;

Game *game = nullptr;

int main(int argc, char *argv[]) {
    game = new Game();
    game->init("frog quest", 800, 640, false);

    const int fps = 60;
    const int frameDelay = 1000 / fps;

    Uint32 frameStart;
    int frametime;

    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frametime = SDL_GetTicks() - frameStart;
        if (frameDelay > frametime) {
            SDL_Delay(frameDelay - frametime);
        }
    }
    game->clean();
}