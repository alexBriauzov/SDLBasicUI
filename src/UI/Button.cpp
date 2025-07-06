#include "Button.h"
#include <iostream>

Button::Button(int x, int y, int w, int h, std::string textureTag): UIElement(x, y){
	shadow = new Image(x + 5, y + 5, w, h, textureTag);
	shadow->textureColor = {10,10,10};
	shadow->opacity = 0.9;
	shadow->setLayer(-1);
	background = new Image(x, y, w, h, textureTag);
	background->setLayer(0);

	children.push_front(shadow);
	children.push_front(background);

	blocksMouseTracing = true;

	onLClick = onElementLeftClickDefault;
	onRClick = onElementRightClickDefault;
	onEnter = onElementEnterDefault;
	onExit = onElementExitDefault;
}

Button::Button(int x, int y, std::string textureTag, std::string text): UIElement(x, y){
	label = new Label(x, y, text);
	label->setLayer(1);
	width = label->width;
	height = label->height;
	shadow = new Image(x + 5, y + 5, width, height, textureTag);
	shadow->textureColor = {10,10,10};
	shadow->opacity = 0.9;
	shadow->setLayer(-1);
	background = new Image(x, y, width, height, textureTag);
	background->setLayer(0);

	children.push_front(shadow);
	children.push_front(background);
	children.push_front(label);

	blocksMouseTracing = true;

	onLClick = onElementLeftClickDefault;
	onRClick = onElementRightClickDefault;
	onEnter = onElementEnterDefault;
	onExit = onElementExitDefault;
}

Button::~Button(){
}

bool Button::onElementLeftClickDefault(UIElement* element){
	std::cout << "pressed button left click\n";
	return true;
}

bool Button::onElementRightClickDefault(UIElement* element){
	std::cout << "pressed button right click\n";
	return true;
}

bool Button::onElementEnterDefault(UIElement* element){
	if(((Button*)element)->background->textureColor.b > 120){
		((Button*)element)->background->textureColorMult = 0.8;
	} else {
		((Button*)element)->background->textureColorMult = 1.6;
	}
	return true;
}

bool Button::onElementExitDefault(UIElement* element){
	if(((Button*)element)->background->textureColor.b > 120){
		((Button*)element)->background->textureColorMult = 1;
	} else {
		((Button*)element)->background->textureColorMult = 1;
	}
	return true;
}