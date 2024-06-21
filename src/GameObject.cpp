#include "GameObject.h"

//using namespace std;

GameObject::GameObject(const char *texturesheet, int x = 0, int y = 0) {
    objtexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    destrect.x = xpos;
    destrect.y = ypos;
    destrect.w = 100;
    destrect.h = 100;
}

void GameObject::update() {

}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objtexture, nullptr, &destrect);

}

GameObject::~GameObject() = default;

void GameObject::Clean() {
    SDL_DestroyTexture(objtexture);
}

Player::Player(const char *texturesheet, int x, int y, const char *frame = "1", const char *type = ".png") : GameObject(
        (string(texturesheet) + string(frame) + string(type)).c_str(), x, y) {
    this->frame = frame;
    this->textureSheet = texturesheet;
    this->type = type;
    timer = new DisplayTimer("../assets/gamefont4.ttf", 650, 60, 34);
    score = new Score("../assets/gamefont4.ttf", 650, 0, 34, timer);
    movingDown = movingUp = movingLeft = movingRight = false;
    TextureManager::LoadTexture("../assets/frog1.png");
    TextureManager::LoadTexture("../assets/frog2.png");
    TextureManager::LoadTexture("../assets/frog3.png");
    TextureManager::LoadTexture("../assets/frog4.png");
    TextureManager::LoadTexture("../assets/frog5.png");
    TextureManager::LoadTexture("../assets/frog6.png");
    TextureManager::LoadTexture("../assets/frog7.png");
    TextureManager::LoadTexture("../assets/frog8.png");
    TextureManager::LoadTexture("../assets/frog9.png");
    TextureManager::LoadTexture("../assets/frog10.png");
    TextureManager::LoadTexture("../assets/frog11.png");
    TextureManager::LoadTexture("../assets/frog12.png");
    TextureManager::LoadTexture("../assets/frog13.png");
    TextureManager::LoadTexture("../assets/frog14.png");
}

void Player::update() {
    int mapWidth = 20 * 36;
    int mapHeight = 20 * 26;

    if (movingDown && destrect.y <= mapHeight) {
        destrect.y += 10;
    } else if (movingUp && destrect.y >= 0) {
        destrect.y -= 10;
    } else if (movingLeft && destrect.x >= 0) {
        destrect.x -= 10;
    } else if (movingRight && destrect.x <= mapWidth) {
        destrect.x += 10;
    }
}

void Player::Render() {
    string path;

    if (movingDown) {
        static int framecounter = 12;
        framecounter = framecounter < 14 ? framecounter + 1 : 12;
        path = textureSheet + std::to_string(framecounter) + type;
        TextureManager::Draw( path,nullptr ,&destrect);
        score->Render();
        timer->Render();
    } else if (movingUp) {
        static int framecounter = 6;
        framecounter = framecounter < 8 ? framecounter + 1 : 6;
        path = textureSheet + std::to_string(framecounter) + type;
        TextureManager::Draw( path,nullptr ,&destrect);
    } else if (movingLeft) {
        static int framecounter = 9;
        framecounter = framecounter < 11 ? framecounter + 1 : 9;
        path = textureSheet + std::to_string(framecounter) + type;
        TextureManager::Draw( path,nullptr ,&destrect);
    } else if (movingRight) {
        static int framecounter = 3;
        framecounter = framecounter < 5 ? framecounter + 1 : 3;
        path = textureSheet + std::to_string(framecounter) + type;
        TextureManager::Draw( path,nullptr ,&destrect);
    } else {
        frame = frame == "1" ? "2" : "1";
        path = textureSheet + frame + type;
        TextureManager::Draw( path,nullptr ,&destrect);
    }
    score->Render();
    timer->Render();


    SDL_Delay(30);

}

Player::~Player() = default;

int Player::getHighScore() const {
    return highScore;
}

void Player::Clean() {
//    DisplayTimer::Clean();
//    Score::Clean();
}


Fruit::Fruit(const char *texturesheeet, int size, int x, int y, Player *p, Mix_Chunk *eat_w) : GameObject(texturesheeet,
                                                                                                          x, y) {
    player = p;
    destrect.h = size;
    destrect.w = size;
    angle = 0;
    eat = eat_w;
    eaten = false;
}

int prevScore = 0;

Fruit::~Fruit() = default;

void Fruit::update() {

    static Uint32 lifeStart = SDL_GetTicks();
    static int lifetime = 10000;

    int reduceFactor = 10;
    SDL_Rect small = {player->getpos()->x + reduceFactor / 2, player->getpos()->y + reduceFactor / 2,
                      player->getpos()->h - reduceFactor, player->getpos()->w - reduceFactor};

    if (SDL_HasIntersection(&destrect, &small)) {
        player->score->update();
        std::cout << "intersection" << std::endl;
        destrect.x = -100;
        destrect.y = -100;
        eaten = true;
    }

    if (Score::score != prevScore) {
        Mix_PlayChannel(-1, eat, 0);
    }
    prevScore = Score::score;
    player->timer->update();
    angle += 4;
}

void Fruit::Render() {
    SDL_RenderCopyEx(Game::renderer, objtexture, nullptr, &destrect, angle, nullptr, SDL_FLIP_NONE);
}

void Fruit::updateLocation(int x, int y){
    destrect.x = x;
    destrect.y = y;
    setEaten(false);
}

Score::Score(const char *texturesheeet, int x, int y, int size, DisplayTimer *timer) : GameObject(texturesheeet, x, y) {
    fontsize = size;
    fontpath = string(texturesheeet);
    font = TTF_OpenFont(texturesheeet, size);
    if (!font) {
        std::cout << "error loading font:" << TTF_GetError() << std::endl;
    }
    textcolor = {255, 255, 255};
    score = 0;
    this->timer = timer;
}

Score::~Score() = default;

const int TIME_INCREASE = 2000;

void Score::update() {
    score++;
    timer->increaseTime(TIME_INCREASE);
//    Mix_PlayChannel(1, eat_w, 0);
    cout << score;
}

void Score::Render() {
    string scoreText = "Score: " + to_string(score);
    SDL_Surface *temp = TTF_RenderText_Blended(font, scoreText.c_str(), textcolor);
    if (temp == nullptr) {
        std::cout << "score surface not created" << std::endl;
    }
    SDL_Texture *scoreTex = SDL_CreateTextureFromSurface(Game::renderer, temp);
    if (scoreTex == nullptr) {
        std::cout << "score texture not created" << std::endl;
    }

    SDL_Rect scoreRect;
    scoreRect.x = destrect.x - 50;
    scoreRect.y = destrect.y + 20;
    scoreRect.w = 150;
    scoreRect.h = 40;

    SDL_RenderCopy(Game::renderer, scoreTex, nullptr, &scoreRect);

    SDL_FreeSurface(temp);
    SDL_DestroyTexture(scoreTex);
}

int Score::score = 0;

void Score::resetScore() {
    score = 0;
}

//void Score::Clean() {
//    TTF_CloseFont(font);
//
//}

const int GAME_TIME = 5000; //use to increase/decrease allowed game time (60000->60s)

DisplayTimer::DisplayTimer(const char *textureSheet, int x, int y, int size) : GameObject(textureSheet, x, y) {
    fontsize = size;
    fontpath = string(textureSheet);
    font = TTF_OpenFont(textureSheet, size);
    if (!font) {
        std::cout << "error loading font:" << TTF_GetError() << std::endl;
    }
    textcolor = {255, 255, 255};
    time = GAME_TIME;
    startTime = SDL_GetTicks();
}

void DisplayTimer::update() {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - startTime;
    if (elapsedTime >= 1000) {
        time -= 1000;
        startTime = currentTime;
    }
}

DisplayTimer::~DisplayTimer() = default;


void DisplayTimer::increaseTime(Uint32 time_a) {

    if(this->time<=7000)
    {this->time += time_a; }
}

void DisplayTimer::Render() {
    Uint32 timeInSeconds = time / 1000;
    SDL_Surface *temp = TTF_RenderText_Blended(font, to_string(timeInSeconds).c_str(), textcolor);
    if (temp == nullptr) {
        std::cout << "timer surface not created" << std::endl;
    }
    SDL_Texture *timerTex = SDL_CreateTextureFromSurface(Game::renderer, temp);
    if (timerTex == nullptr) {
        std::cout << "time texture not created" << std::endl;
    }

    SDL_Rect timerRect;
    timerRect.x = destrect.x + 17;
    timerRect.y = destrect.y - 10;
    timerRect.w = 100;
    timerRect.h = 100;

    SDL_RenderCopy(Game::renderer, timerTex, nullptr, &timerRect);

    SDL_FreeSurface(temp);
    SDL_DestroyTexture(timerTex);
}

//void DisplayTimer::Clean() {
//    TTF_CloseFont(font);
//}

StartScreen::StartScreen(const char *textureSheet, int x, int y, int size) : GameObject(textureSheet, x, y) {
    TextureManager::LoadTexture("../assets/bgstart.png");
    fontsize = size;
    fontpath = string(textureSheet);
    font = TTF_OpenFont(textureSheet, size);
    if (!font) {
        std::cout << "error loading font:" << TTF_GetError() << std::endl;
    }
    textcolor = {255, 255, 255};
}

StartScreen::~StartScreen() = default;

void StartScreen::update() {}


void StartScreen::Render() {
    static SDL_Rect dest = {0, 0, 800, 640};
    TextureManager::Draw("../assets/bgstart.png", nullptr,&dest );

    string startText = "Press any key to start";
    string titleText = "FROG QUEST";

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / 500;
    if (seconds % 2 == 0) {
        textcolor = {153, 13, 39};
    } else {
        textcolor = {13, 82, 153};
    }

    SDL_Surface *temp = TTF_RenderText_Blended(font, startText.c_str(), textcolor);
    SDL_Surface *titleTemp = TTF_RenderText_Blended(font, titleText.c_str(), textcolor);

    if (temp == nullptr || titleTemp == nullptr) {
        std::cout << "start screen surface not created" <<std::endl;
    }

    SDL_Texture *startTex = SDL_CreateTextureFromSurface(Game::renderer, temp);
    SDL_Texture *titleTex = SDL_CreateTextureFromSurface(Game::renderer, titleTemp);

    if (startTex == nullptr || titleTex == nullptr) {
        std::cout << "start screen texture not created" << std::endl;
    }

    int screenCenterX = 800 / 2;
    int screenCenterY = 600 / 2 + 150;
    int textWidth = (int) (temp->w * 0.7);
    int textHeight = (int) (temp->h * 0.7);

    int titleTextWidth = titleTemp->w * 2;
    int titleTextHeight = titleTemp->h * 2;
    SDL_Rect titleDestRect;
    titleDestRect.x = screenCenterX - titleTextWidth / 2;
    titleDestRect.y = screenCenterY - titleTextHeight / 2 - 50;
    titleDestRect.w = titleTextWidth;
    titleDestRect.h = titleTextHeight;
    SDL_RenderCopy(Game::renderer, titleTex, nullptr, &titleDestRect);

    destrect.x = screenCenterX - textWidth / 2;
    destrect.y = screenCenterY - textHeight / 2;
    destrect.w = textWidth;
    destrect.h = textHeight;
    SDL_RenderCopy(Game::renderer, startTex, nullptr, &destrect);

    SDL_FreeSurface(temp);
    SDL_FreeSurface(titleTemp);
    SDL_DestroyTexture(startTex);
    SDL_DestroyTexture(titleTex);
}

void StartScreen::Clean() {
    TTF_CloseFont(font);
}


EndScreen::EndScreen(const char *textureSheet, int x, int y, int size, int highScore) : GameObject(textureSheet, x, y) {
    TextureManager::LoadTexture("../assets/bgend.png");
    fontsize = size;
    fontpath = string(textureSheet);
    font = TTF_OpenFont(textureSheet, size);
    if (!font) {
        cout << "error loading font:" << TTF_GetError() << endl;
    }
    textcolor = {255, 255, 255};
    this->highScore = highScore;
}

EndScreen::~EndScreen() {
    TTF_CloseFont(font);
}

void EndScreen::Render() {
    static SDL_Rect dest = {0, 0, 800, 640};
    TextureManager::Draw("../assets/bgend.png",nullptr,&dest);
    std::vector<std::string> lines = {
            "Game Over! High Score: " + std::to_string(highScore),
            "Press R to restart. Or Q to quit."
    };

    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / 500;
    if (seconds % 2 == 0) {
        textcolor = {153, 13, 39};
    } else {
        textcolor = {13, 82, 153};
    }

    int screenCenterX = 800 / 2;
    int screenCenterY = 600 / 2 + 200;

    for (size_t i = 0; i < lines.size(); ++i) {
        SDL_Surface *temp = TTF_RenderText_Blended(font, lines[i].c_str(), textcolor);
        if (temp == nullptr) {
            std::cout << "End screen surface not created" << std::endl;
            continue;
        }
        SDL_Texture *endTex = SDL_CreateTextureFromSurface(Game::renderer, temp);
        if (endTex == nullptr) {
            std::cout << "End screen texture not created" << std::endl;
            SDL_FreeSurface(temp);
            continue;
        }

        const double SCALING_FACTOR = 0.9;
        int textWidth = (int) (temp->w * SCALING_FACTOR);
        int textHeight = (int) (temp->h * SCALING_FACTOR);
        destrect.x = screenCenterX - textWidth / 2;
        destrect.y = screenCenterY - textHeight / 2 + i * (textHeight + 5) + 50;
        destrect.w = textWidth;
        destrect.h = textHeight;

        SDL_RenderCopy(Game::renderer, endTex, nullptr, &destrect);
        SDL_FreeSurface(temp);
        SDL_DestroyTexture(endTex);
    }
}

void EndScreen::setHighScore(int i) {
    highScore = i;
}

Uint32 DisplayTimer::getTime() const {
    return time;
}

void DisplayTimer::resetTime(Uint32 time_a) {
    this->time = time_a;
    startTime = SDL_GetTicks();
}



