#include "UIElement.h"

UIElement::UIElement(int x, int y){
	tag = currentGlobalTagTicker++;
    posX = x;
    posY = y;
    blocksMouseTracing = false;
	layer = 0;
	onRClick = NULL;
	onLClick = NULL;
	onEnter = NULL;
	onExit = NULL;
	needsUpdate = false;
	scale = 1.0;
	uiList.push_front(this);
	uiListNeedsSorting = true;
}

UIElement::~UIElement(){
	for (UIElement* elem : children){
		delete(elem);
	}
	children.clear();
	uiList.remove(this);
	if(UIElement::tagetedElement == this){
		UIElement::tagetedElement = NULL;
	}
	uiListNeedsSorting = true;
}

void UIElement::setLayer(int newLayer){
	for (UIElement* child : children) {
		child->setLayer(newLayer - layer + child->layer);
    }
	layer = newLayer;
	uiListNeedsSorting = true;
}

void UIElement::setPosition(int x, int y){
	for (UIElement* child : children) {
		child->setPosition(x - posX + child->posX, y - posY + child->posY);
    }
	posX = x;
	posY = y;
}

void UIElement::update(long long tick){
	
}

void UIElement::sortElements(){
	uiList.sort([](UIElement* lhs, UIElement* rhs) { return lhs->layer < rhs->layer; });
	uiListNeedsSorting = false;
}