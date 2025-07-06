#include "Image.h"

Image::Image(int posX, int posY, int imageWidth, int imageHeight, std::string textureTag): UIElement(posX, posY){
	texture = textureTag;

  	width = imageWidth;
	height = imageHeight;
	frameOffsetX = 0;
    frameOffsetY = 0;
}

Image::~Image(){
}
