#include "Game.h"
#include  "GameObject.h"
#include "Map.h"


Player * player;
Map* map;
SDL_Renderer* Game::renderer =nullptr;

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        }

        isRunning = true;
    }
    player = new Player("../assets/frog.png",0,0);
    map=new Map();

}

void Game::handleEvents()
{
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT :
            isRunning = false;
        break;
        case SDL_KEYDOWN :
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    player->update(0,-32);
                    break;
                case SDLK_DOWN:
                    player->update(0,+32);
                    break;
                case SDLK_RIGHT:
                    player->update(32,0);
                    break;
                case SDLK_LEFT:
                    player->update(-32,0);
                    break;
                    default:
                        player->update(0,0);
                        break;
            }
        default:
            break;
    }
}

void Game::update()
{


}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    player->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
