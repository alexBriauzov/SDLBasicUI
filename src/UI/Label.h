#pragma once
#include "UIElement.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"

class Label: public UIElement
{
public:

    TTF_Font* textFont;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    std::string text;
    SDL_Color textColor = {0,0,0};
    // set to zero if you dont wat text wrapping
    int wrapping = 0;

    //set text in this gameobject to be newText
    void setText(std::string newText);

    bool setTextFontSize(int size);

    virtual ~Label();

    Label(int posX, int posY, std::string text);

    inline static TTF_Font* font60;
	inline static TTF_Font* font45;
	inline static TTF_Font* font30;

};