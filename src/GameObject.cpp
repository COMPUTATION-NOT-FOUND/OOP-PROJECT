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
            destrect.x+=speedx;
            destrect.y+=speedy;
            }

void Player::Render() {
    frame=frame=="1"?"2":"1";
    std::string path =texturesheet+frame+type;
    objtexture=TextureManager::LoadTexture(path.c_str());
    SDL_Delay(30);
    SDL_RenderCopy(Game::renderer,objtexture,NULL,&destrect);

}
Player::~Player() {
    // Empty destructor
}