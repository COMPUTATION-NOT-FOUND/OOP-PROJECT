#include "GameObject.h"
#include "TextureManager.h"
#include <string>

 GameObject::GameObject( int size,int x =0,int y=0){
     xpos=x;
     ypos=y;
     destrect.x=xpos;
     destrect.y=ypos;
     destrect.w=size;
     destrect.h=size;
     objtexture= nullptr;
 }

 SDL_Rect GameObject::GetDestrect() {
    return destrect;
}

//void GameObject::update(){
//
//
//
// }
//void GameObject::Render(){
//     SDL_RenderCopy(Game::renderer,objtexture,NULL,&destrect);
//
//}
GameObject::~GameObject() {
    // Empty destructor
}

Player::Player(const char* texturesheet,int size ,int x,int y,const char* frame="1",const char* type=".png" ):GameObject( size , x, y){
    speedx=0;
    speedy=0;
    this->frame=frame;
    this->texturesheet=texturesheet;
    this->type=type;
}

void Player::update() {
        // Calculate the potential new position of the player
        int newX = destrect.x + speedx;
        int newY = destrect.y + speedy;

        // Define the bounds of the map in pixels
        int mapWidth = 20 * 40; // 20 columns * 40 pixels per column (adjust as needed)
        int mapHeight = 20 * 32; // 20 rows * 32 pixels per row (adjust as needed)

        // Check if the new X position is within bounds
        if (newX >= 0 && newX + destrect.w <= mapWidth) {
            destrect.x = newX; // Update the player's x position
        } else {
            // Prevent player from going out of bounds in the X direction
            if (newX < 0) {
                destrect.x = 0;
            } else {
                destrect.x = mapWidth - destrect.w;
            }
        }

        // Check if the new Y position is within bounds
        if (newY >= 0 && newY + destrect.h <= mapHeight) {
            destrect.y = newY; // Update the player's y position
        } else {
            // Prevent player from going out of bounds in the Y direction
            if (newY < 0) {
                destrect.y = 0;
            } else {
                destrect.y = mapHeight - destrect.h;
            }
        }
    }





void Player::Render(){
std::string path;

if(speedx >0){
  static int framecounter =3;

framecounter= framecounter<5 ?framecounter+1:3;

path = texturesheet + std::to_string(framecounter) + type;
objtexture = TextureManager::LoadTexture(path.c_str());

SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
    //SDL_Delay(30);
}
else if(speedx <0){
    static int framecounter =9;

    framecounter= framecounter<11 ?framecounter+1:9;
    path = texturesheet + std::to_string(framecounter) + type;
    objtexture = TextureManager::LoadTexture(path.c_str());

SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
else if(speedy >0){
    static int framecounter =12;

    framecounter= framecounter<14 ?framecounter+1:12;
    path = texturesheet + std::to_string(framecounter) + type;
    objtexture = TextureManager::LoadTexture(path.c_str());

SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
else if(speedy <0){
    static int framecounter =6;

    framecounter= framecounter<8 ?framecounter+1:6;
    path = texturesheet + std::to_string(framecounter) + type;
    objtexture = TextureManager::LoadTexture(path.c_str());

SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
else{
static int framecounter =1;
        framecounter = framecounter == 1 ? 2: 1;
        path = texturesheet + std::to_string(framecounter) + type;
        objtexture = TextureManager::LoadTexture(path.c_str());

        SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
    //SDL_Delay(30);
}
}

Player::~Player() {
    // Empty destructor
}


Fruit::Fruit(const char *texturesheeet, int size, int x, int y,Player* p): GameObject(size,x,y) , player(p){
    objtexture=TextureManager::LoadTexture(texturesheeet);

}

void Fruit::update() {
    static Uint32 lifestart=SDL_GetTicks();
   static int lifetime=3000;
    if( lifetime<(SDL_GetTicks()-lifestart) || IsInteresct()){
        int mapWidth = 20 * 40;
        int mapHeight = 20 * 32;
        int newX = rand() % (mapWidth - destrect.w);
        int newY = rand() % (mapHeight - destrect.h);
        destrect.x = newX;
        destrect.y = newY;
        lifestart=SDL_GetTicks();
    }

}

void Fruit::Render() {
    SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}

bool Fruit::IsInteresct() {
    SDL_Rect playerRect;
    if (player != nullptr) {
        playerRect = player->GetDestrect();
    } else {
        // Handle the case when player is nullptr
        return false;
    }
    return SDL_HasIntersection(&destrect, &playerRect);
//        return SDL_HasIntersection(&destrect, &player->GetDestrect());
}