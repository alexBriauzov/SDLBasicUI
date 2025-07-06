#include "Animation.h"
#include <iostream>

Animation::Animation(UIElement* tar, std::string t){
    target = tar;
    state = 0;
    isPlaying = false;
    isFinished = false;
    if(t == "bounce") {update = bounceAnimation;}
    else {
        target = NULL;
        update = defaultAnimation;
    }
    targetTag = tar->tag;
	animationList.push_front(this);

}

Animation::~Animation(){
    	animationList.remove(this);
}

void Animation::start(){
    isPlaying = true;
}


void Animation::defaultAnimation(Animation* animation){
    animation->isFinished = true;
}

void Animation::bounceAnimation(Animation* animation){
    if(animation->targetTag != animation->target->tag){
        animation->isPlaying = false;
        animation->isFinished = true;
        return;
    }
    if(animation->state == 0){
        animation->targetInitialX = animation->target->posX;
        animation->targetInitialY = animation->target->posY;
        animation->state = 1;
        return;
    }
    if(animation->state < 25){
        animation->target->posY = animation->targetInitialY + -50*sin(animation->state*(0.04)*3.14);

        animation->state++;
        return;
    }
    animation->target->posX = animation->targetInitialX;
    animation->target->posY = animation->targetInitialY;
    animation->isPlaying = false;
    animation->isFinished = true;
}