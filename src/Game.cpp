#include "Game.h"
#include  "GameObject.h"
#include "Map.h"
#include <random>


Player *player;
Map *map1;
std::vector<Fruit *> fruits;
SDL_Renderer *Game::renderer = nullptr;
StartScreen *startScreen;
EndScreen *endScreen;

Mix_Music *start = nullptr;
Mix_Music *game_w = nullptr;
Mix_Music *end_w = nullptr;
Mix_Chunk *eat = nullptr;
Mix_Chunk *die = nullptr;


static const int rand_offset_x = 20;
static const int rand_offset_y = 20;


Game::Game() = default;

Game::~Game() = default;

void Game::init(const char *title, int width, int height, bool fullscreen) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disX(20, 780-20);
    std::uniform_int_distribution<int> disY(20, 600-30);

    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        if (TTF_Init() == -1) {
            cerr << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        }
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        }
        isRunning = true;
    }
    eat = Mix_LoadWAV("../assets/eat.wav");
    int rX = disX(gen);
    int rY = disY(gen);
    player = new Player("../assets/frog", rX, rY, "1", ".png");
    map1 = new Map();
    startScreen = new StartScreen("../assets/gamefont3.ttf", 650, 180, 34);
    endScreen = new EndScreen("../assets/gamefont3.ttf", 650, 180, 34, player->getHighScore());
    start = Mix_LoadMUS("../assets/start.wav");
    game_w = Mix_LoadMUS("../assets/game.wav");
    end_w = Mix_LoadMUS("../assets/end.wav");
    die = Mix_LoadWAV("../assets/die.wav");


    Mix_PlayMusic(start, -1);

    for (int i = 0; i < 5; i++) {
        int randX = disX(gen);
        int randY = disY(gen);
        auto *fruit = new Fruit("../assets/Fruit1.png", 32, randX, randY, player, eat);
        fruits.push_back(fruit);
    }

}

//show start, show game, show end

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (showStart) {
                showStart = false;
                showGame = true;
                Mix_HaltMusic();
                Mix_PlayMusic(game_w, -1);
            } else if (showEnd && event.key.keysym.sym == SDLK_r) {
                reset();
            } else if (showEnd && event.key.keysym.sym == SDLK_q) {
                isRunning = false;
            } else if (showGame) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        player->movingUp = true;
                        break;
                    case SDLK_DOWN:
                        player->movingDown = true;
                        break;
                    case SDLK_LEFT:
                        player->movingLeft = true;
                        break;
                    case SDLK_RIGHT:
                        player->movingRight = true;
                        break;
                }
            }
            break;
        case SDL_KEYUP:
            if (showGame) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        player->movingUp = false;
                        break;
                    case SDLK_DOWN:
                        player->movingDown = false;
                        break;
                    case SDLK_LEFT:
                        player->movingLeft = false;
                        break;
                    case SDLK_RIGHT:
                        player->movingRight = false;
                        break;
                }
            }
            break;
    }
    SDL_Delay(30);
}

void Game::update() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disX(20, 780-20);
    std::uniform_int_distribution<int> disY(20, 600-20);

    if (showGame) {
        player->update();

        bool eatenAll = true;
        for (auto &f: fruits) {
            f->update();
            if (!f->isEaten()) {
                eatenAll = false;
            }
        }



        if(eatenAll){
            for (auto &f: fruits) {
                int randX = disX(gen);
                int randY = disY(gen);
                f->updateLocation(randX, randY);
            }
        }

        if (player->timer->getTime() <= 200) {
            if (Score::score > player->getHighScore()) {
                player->highScore = Score::score;
                endScreen->setHighScore(player->highScore);
            }
            showGame = false;
            showEnd = true;
            Mix_HaltMusic();
            Mix_PlayChannel(-1, die, 0);
            Mix_PlayMusic(end_w, -1);
        }
    }
}

void Game::render() const {



    if (showStart) {
        startScreen->Render();
    } else if (showGame) {
        map1->DrawMap();
        player->Render();
        for (auto &f: fruits) {
            f->Render();
        }
    } else if (showEnd) {
        endScreen->Render();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    player->Clean();

    for (auto &f: fruits) {
        f->Clean();
    }

    Mix_FreeMusic(start);
    Mix_FreeMusic(game_w);
    Mix_FreeMusic(end_w);
    Mix_FreeChunk(eat);
    Mix_FreeChunk(die);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}

void Game::reset() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disX(20, 780);
    std::uniform_int_distribution<int> disY(20, 600);
    delete (player);
    int rX = disX(gen);
    int rY = disY(gen);
    player = new Player("../assets/frog", rX, rY, "1", ".png");
    for (auto &f: fruits) {
        delete (f);
    }
    fruits.clear();
    for (int i = 0; i < 5; i++) {
        int randX = disX(gen);
        int randY = disY(gen);
        auto *fruit = new Fruit("../assets/Fruit1.png", 32, randX, randY, player, eat);
        fruits.push_back(fruit);
    }
    player->timer->resetTime(5000);
    Score::resetScore();
    showEnd = false;
    showGame = true;
    Mix_HaltMusic();
    Mix_PlayMusic(game_w, -1);
    player->movingDown = player->movingRight = player->movingLeft = player->movingUp = false;
}
