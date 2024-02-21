#include "Game.h"
#include "TextureManager.h"
#include  "GameObject.h"


GameObject* player;
SDL_Texture* PlayerTex;
Game::Game()
{}

Game::~Game()
{}

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
	player=new GameObject("assets/frog.PNG",renderer,0,0);
	//SDL_Surface* tempsurface = IMG_Load("assets/frog.PNG");
	//PlayerTex= SDL_CreateTextureFromSurface(renderer,tempsurface);
	//SDL_FreeSurface(tempsurface);

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
	default:
		break;
	}
}

void Game::update()
{
	cnt++;
	std::cout << cnt << std::endl;
	player->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer,PlayerTex,NULL,NULL);
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

