#include "Label.h"
#include "TextureManager.h"

Label::Label(int posX, int posY, std::string newText): UIElement(posX, posY){
	textFont = font45;
	textSurface = NULL;
    textTexture = NULL;
	wrapping = 0;
	text = " ";
	setText(newText);
}


Label::~Label(){
}

void Label::setText(std::string newText){
	if(text == newText){
		//return;
	}
	if(newText.empty()){
		newText = " "; //for some reson TTF_RenderText_Blended_Wrapped returns a NULL if string is ""
	}
	text = newText;
	textSurface = TTF_RenderText_Blended_Wrapped(textFont, text.c_str(), textColor, wrapping);
  	width = textSurface ->w;
	height = textSurface ->h;
	if(textTexture != NULL){
		SDL_DestroyTexture(textTexture);
	}
	textTexture =  SDL_CreateTextureFromSurface(TextureManager::renderer,textSurface);
	SDL_FreeSurface(textSurface);
}

bool Label::setTextFontSize(int size){
	if(size == 60)
		this->textFont = font60;
	if(size == 45)
		this->textFont = font45;
	if(size == 30)
		this->textFont = font30;
	return true;
}