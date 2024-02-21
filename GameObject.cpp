#include "GameObject.h"
#include "TextureManager.h"

 GameObject::GameObject(const char* texturesheet ,SDL_Renderer* ren,int x,int y){

    renderer=ren;
    objtexture=TextureManager::LoadTexture(texturesheet,ren);
    xpos=x;
    ypos=y;

 }

    void GameObject::update(){
        
      //xpos++;
      //ypos++;
        srcrect.h=64;
        srcrect.w=64;
        srcrect.x=0;
        srcrect.y=0;

        destrect.x =xpos;
        destrect.y=ypos;
        destrect.w=128;
        destrect.h=128;

        


    }
    void GameObject::Render(){

      SDL_RenderCopy(renderer,objtexture,&srcrect,&destrect);



    }
