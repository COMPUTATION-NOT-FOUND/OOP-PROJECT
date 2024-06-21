#pragma once

#include "Game.h"
#include "SDL_mixer.h"
#include "TextureManager.h"



class Score;

class DisplayTimer;

class StartScreen;

class EndScreen;

using namespace std;

class GameObject {
protected:
    int xpos;
    int ypos;
    SDL_Texture *objtexture;
    SDL_Rect destrect{};


public:
    GameObject(const char *texturesheeet, int x, int y);

    ~GameObject();

    virtual void update();

    virtual void Render();

    virtual void Clean();

    virtual SDL_Rect *getpos() { return &destrect; }
};

class Player : public GameObject {
public:
    //int speedx;
    //int speedy;
    bool movingUp, movingDown, movingLeft, movingRight;
    string frame;
    string textureSheet;
    string type;
    Score *score;
    int highScore = 0;
    DisplayTimer *timer;

    Player(const char *texturesheeet, int x, int y, const char *frame, const char *type);

    ~Player();

    [[nodiscard]] int getHighScore() const;

    void update() override;

    void Render() override;

    void Clean() override;
};

class Fruit : public GameObject {
public:
    Player *player;
    double angle;
    Mix_Chunk *eat;
    bool eaten;

    Fruit(const char *texturesheeet, int size, int x, int y, Player *p, Mix_Chunk *eat);

    ~Fruit();

    void update() override;

    void Render() override;

    [[nodiscard]] bool isEaten() const { return eaten; }

    void setEaten(bool b) { eaten = b; }

    void updateLocation(int x, int y);
};

class Score : public GameObject {
private:
    int fontsize;
    string fontpath;
    TTF_Font *font;
    SDL_Color textcolor{};
    DisplayTimer *timer;

public:
    Score(const char *texturesheeet, int x, int y, int size, DisplayTimer *timer);

    ~Score();

    static int score;

    void update() override;

    void Render() override;

//    static void Clean();

    static void resetScore();
};

class DisplayTimer : public GameObject {
private:
    int fontsize;
    string fontpath;
    Uint32 time;
    Uint32 startTime; // Add this line
    TTF_Font *font;
    SDL_Color textcolor{};

public:
    DisplayTimer(const char *textureSheet, int x, int y, int size);

    ~DisplayTimer();

    void update();

    void Render();

//    static void Clean() override;

    void increaseTime(Uint32 time_a);

    void resetTime(Uint32 time);

    Uint32 getTime() const;
};

class StartScreen : public GameObject {
private:
    int fontsize;
    string fontpath;
    TTF_Font *font;
    SDL_Color textcolor{};

public:
    StartScreen(const char *textureSheet, int x, int y, int size);

    ~StartScreen();

    void update();

    void Render();

    void Clean();
};

class EndScreen : public GameObject {
private:
    int fontsize;
    string fontpath;
    TTF_Font *font;
    SDL_Color textcolor{};
    int highScore;
public:
    EndScreen(const char *textureSheet, int x, int y, int size, int highScore);

    ~EndScreen();

    void Render();

    void setHighScore(int i);
};


