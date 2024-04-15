#include "GameObject.h"
#include "TextureManager.h"
#include <string>

 GameObject::GameObject(const char* texturesheet,int x=0,int y=0){
     objtexture=TextureManager::LoadTexture(texturesheet);
     xpos=x;
     ypos=y;
     destrect.x=xpos;
     destrect.y=ypos;
     destrect.w=100;
     destrect.h=100;
 }

void GameObject::update(){

//     srcrect.h=64;
//     srcrect.w=64;
//     srcrect.x=0;
//     srcrect.y=0;


 }
void GameObject::Render(){
     SDL_RenderCopy(Game::renderer,objtexture,NULL,&destrect);

}
GameObject::~GameObject() {
    // Empty destructor
}

Player::Player(const char* texturesheet ,int x,int y,const char* frame="1",const char* type=".png" ):GameObject( texturesheet , x, y){
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
path = texturesheet + "3" + type;
objtexture = TextureManager::LoadTexture(path.c_str());
SDL_Delay(30);
SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
else if(speedx <0){
path = texturesheet + "5" + type;
objtexture = TextureManager::LoadTexture(path.c_str());
SDL_Delay(30);
SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
else if(speedy >0){
path = texturesheet + "1" + type;
objtexture = TextureManager::LoadTexture(path.c_str());
SDL_Delay(30);
SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
else if(speedy <0){
path = texturesheet + "4" + type;
objtexture = TextureManager::LoadTexture(path.c_str());
SDL_Delay(30);
SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
else{

        frame = frame == "1" ? "2" : "1";
        path = texturesheet + frame + type;
        objtexture = TextureManager::LoadTexture(path.c_str());
        SDL_Delay(30);
        SDL_RenderCopy(Game::renderer, objtexture, NULL, &destrect);
}
}

Player::~Player() {
    // Empty destructor
}