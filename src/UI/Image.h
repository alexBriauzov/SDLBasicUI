#pragma once
#include "UIElement.h"
#include "SDL2/SDL_render.h"

class Image : public UIElement
{
public:
    
    std::string texture;
    SDL_Color textureColor = {255,255,255};
    double textureColorMult = 1.0;
    double opacity = 1.0;
    int frameOffsetX = 0;
    int frameOffsetY = 0;

    virtual ~Image();

    Image(int posX, int posY, int width, int height, std::string textureTag);

};