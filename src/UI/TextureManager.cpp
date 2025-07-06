#include "TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::getTexture(std::string path){
    if(textures.find(path) != textures.end())
		return textures[path];
    
	SDL_Texture* texture;
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == NULL)
		return NULL;

	textures[path] = texture;

	return texture;
}

bool TextureManager::loadTextureSequence(std::string filePath, int frameRate, int frameWidth, int pivotX, int pivotY){
    if (textureSequences.find(filePath) != textureSequences.end()){
		return false;
	}
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if(texture == NULL){
        return false;
	}
	textureSequences[filePath] = new Texture();
	textureSequences[filePath]->name = filePath;
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_DestroyTexture(texture);
	textureSequences[filePath]->frameCount = w/frameWidth;
	textureSequences[filePath]->frameHeight = h;
	textureSequences[filePath]->frameRate = frameRate;
	textureSequences[filePath]->frameWidth = frameWidth;
	textureSequences[filePath]->framePivotX = pivotX;
	textureSequences[filePath]->framePivotY = pivotY;

	return true;
}


bool TextureManager::loadTexture(std::string filePath, int pivotX, int pivotY){
    if (textureSequences.find(filePath) != textureSequences.end()){
		std::cout << "didnt find texture " << filePath << "\n";
		return false;
	}
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if(texture == NULL){
		std::cout << "couldnt load texture " << filePath << "\n";
        return false;
	}
	textureSequences[filePath] = new Texture();
	textureSequences[filePath]->name = filePath;
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_DestroyTexture(texture);
	textureSequences[filePath]->frameCount = 1;
	textureSequences[filePath]->frameHeight = h;
	textureSequences[filePath]->frameRate = 1;
	textureSequences[filePath]->frameWidth = w;
	textureSequences[filePath]->framePivotX = pivotX;
	textureSequences[filePath]->framePivotY = pivotY;

	return true;
}


Texture* TextureManager::getTextureSequence(std::string filePath){
    if (textureSequences.find(filePath) == textureSequences.end()){
		return textureSequences["assets/default.png"];
    }
    return textureSequences[filePath];
}