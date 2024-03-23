#include "GameObject.h"
#include "TextureManager.h"

 GameObject::GameObject(const char* texturesheet ,int x,int y){
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

Player::Player(const char* texturesheet ,int x,int y):GameObject( texturesheet , x, y){
    speedx=0;
    speedy=0;

}

void Player::update() {
            destrect.x+=speedx;
            destrect.y+=speedy;
            }


