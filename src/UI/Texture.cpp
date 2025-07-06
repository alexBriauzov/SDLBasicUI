#include "Texture.h"
#include <iostream>

SDL_Rect Texture::getFrameRect(long long tick){
    SDL_Rect rect;
    rect.x = frameWidth*((tick/frameRate)%frameCount);
    rect.y = 0;
    rect.w = frameWidth;
    rect.h = frameHeight;
    return rect;
}

Vector2 Texture::getFrameSize(){
    return Vector2(frameWidth, frameHeight);
}