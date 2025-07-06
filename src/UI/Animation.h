#pragma once
#include "UIElement.h"
#include <string>
#include <map>
#include <cmath>

class Animation
{
public:

    UIElement* target = NULL;
    int targetTag = 0;
    double state = 0;
    bool isPlaying = false;
    bool isFinished = false;

    Animation(UIElement* target, std::string tag);
    virtual ~Animation();

    // play the Animation
    void (*update)(Animation* animation) = NULL;

    // play the Animation
    void start();

    // end the Animation
    void stop();

    //list of Animations, animations are removed once they are finished
	inline static std::list<Animation*> animationList;

    static void defaultAnimation(Animation* animation);

    static void bounceAnimation(Animation* animation);



private:

    // inital variables of the target saved to be restored when the animation ends
    int targetInitialX;
    int targetInitialY;


};