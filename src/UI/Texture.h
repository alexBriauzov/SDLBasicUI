#pragma once
#include "SDL2/SDL_render.h"
#include "Vector2.h"
#include <string>

class Texture
{
public:
	// a single texture made of the animation frames in chronological order from left to right
	std::string name;

	// Sizes of a single frame in pixels
	int frameWidth;
	int frameHeight;

	// x Coordinate used for position
	int framePivotX = 0;
	int framePivotY = 0;
	// number of frames in this animation
	// must be frameCount = frames.width/frameWidth;
	long frameCount = 0;
	// number of frame changes that would ideally be called per second
	long frameRate = 0;


	// returns the IntRect coordinates of the necessary frame in the texture from the global tick
	SDL_Rect getFrameRect(long long tick);

	// returns the width and height of a single frame
	Vector2 getFrameSize();

};

