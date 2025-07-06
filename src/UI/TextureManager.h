#pragma once
#include <map>
#include <string>
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_image.h"
#include "Texture.h"

class TextureManager
{
public:

	inline static SDL_Renderer* renderer;
    
    // returns the texture under the given name.
    // if texture is not in textures map, attempts to load it from disk
    // if no file found, returns null
    static SDL_Texture* getTexture(std::string filePath);

    // load a texture sequence (an image made up of frames of equal size placed next to  each other from left to right)
    static bool loadTextureSequence(std::string filePath, int frameRate, int frameWidth, int pivotX, int pivotY);

    // load a normal texture
    static bool loadTexture(std::string filePath, int pivotX, int pivotY);

    static Texture* getTextureSequence(std::string filePath);

private:

    //a map of all textures currently loaded into memory
	//might or might not clear until game closure
	inline static std::map<std::string, SDL_Texture*> textures;

	//a map of all animations currently loaded into memory
	//might or might not clear until game closure
	inline static std::map<std::string, Texture*> textureSequences;
};