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
    player = new Player("../assets/frog",0,0,"1",".png");
    map=new Map();

}

const int ACCELERATION = 2;
const int DECELERATION = 1;
const int MAX_SPEED = 25;

void Game::handleEvents() {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT :
            isRunning = false;
            break;
        case SDL_KEYDOWN :
            switch (event.key.keysym.sym) {

                case SDLK_UP:
                    if (player->speedy > -MAX_SPEED)
                    player->speedy -= ACCELERATION;
                    break;
                case SDLK_DOWN:
                    if (player->speedy < MAX_SPEED)
                    player->speedy += ACCELERATION;
                    break;
                case SDLK_RIGHT:
                    if (player->speedx < MAX_SPEED)
                    player->speedx += ACCELERATION;
                    break;
                case SDLK_LEFT:
                    if (player->speedx > -MAX_SPEED)
                    player->speedx -= ACCELERATION;
                    break;
                default:

                    break;
            }
            break;
        case SDL_KEYUP: {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    while(player->speedy < 0) {
                        player->speedy += DECELERATION;
                        if (player->speedy > 0)
                            player->speedy = 0;
                    }
                    break;
                case SDLK_DOWN:
                    while(player->speedy > 0) {
                        player->speedy -= DECELERATION;
                        if (player->speedy < 0)
                            player->speedy = 0;
                    }
                    break;
                case SDLK_RIGHT:
                    while (player->speedx > 0) {
                        player->speedx -= DECELERATION;
                        if (player->speedx < 0)
                            player->speedx = 0;
                    }
                    break;
                case SDLK_LEFT:
                    while (player->speedx < 0) {
                        player->speedx += DECELERATION;
                        if (player->speedx > 0)
                            player->speedx = 0;
                    }
                    break;
                default:
                    break;

            }
            default:
                break;
        }
    }
    SDL_Delay(30);
}

void Game::update()
{
player->update();

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
