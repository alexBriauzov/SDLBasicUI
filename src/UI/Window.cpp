#include "Window.h"

Window::Window(int w, int h, int l){
    width = w;
    height = h;
    layer = l;
    margin = 10;
    shadow = NULL;
}

Window::~Window(){
    for (std::list<UIElement*>* l : contents){
        for (UIElement* elem : *l){
            delete(elem);
        }
        l->clear();
    }
    contents.clear();
    delete(shadow);
    delete(background);
    delete(frameBottom);
    delete(frameTop);
}

void Window::open(){
    shadow = new Image(posX + 10, posY + 10, width, height, "assets/white.png");
    shadow->setLayer(layer);
    shadow->textureColor = {10,10,10};
    background = new Image(posX, posY, width, height, "assets/white.png");
    background->setLayer(layer + 1);
    background->textureColor = {240,240,240};
    frameBottom = new Image(posX+8, posY+8, width-16, height-16, "assets/white.png");
    frameBottom->setLayer(layer + 2);
    frameBottom->textureColor = {10,10,10};
    frameTop = new Image(posX+10, posY+10, width-20, height-20, "assets/white.png");
    frameTop->setLayer(layer + 3);
    frameTop->textureColor = {240,240,240};
    updatePos();
}

UIElement* Window::addText(std::string text, Alignment alignment, bool newLine){
    UIElement* e = new Label(posX,posY, text);
    e->setLayer(layer + 4);
    e->alignment = alignment;
    if(newLine || contents.empty()){
        std::list<UIElement*>* list = new std::list<UIElement*>();
        contents.push_back(list);
    }
    contents.back()->push_back(e);
    return e;
}

UIElement* Window::addImage(std::string textureTag, Alignment alignment, bool newLine){
    UIElement* e = new Image(posX,posY,10,10, textureTag);
    e->setLayer(layer + 4);
    e->alignment = alignment;
    if(newLine || contents.empty()){
        std::list<UIElement*>* list = new std::list<UIElement*>();
        contents.push_back(list);
    }
    contents.back()->push_back(e);
    return e;
}

UIElement* Window::addButton(std::string text, std::string textureTag, Alignment alignment, bool newLine){
    UIElement* e = new Button(posX, posY, textureTag, text);
    e->setLayer(layer + 4);
    e->alignment = alignment;
    if(newLine || contents.empty()){
        std::list<UIElement*>* list = new std::list<UIElement*>();
        contents.push_back(list);
    }
    contents.back()->push_back(e);
    return e;
}

void Window::autoResize(){
    int newWidth = 0;
    int newHeight = 20 + margin;
    for (std::list<UIElement*>* l : contents){
        int maxHeight = 0;
        int lineWidth = listElementWidth(l);
        for (UIElement* elem : *l){
            if(maxHeight < elem->height*elem->scale)
                maxHeight = elem->height*elem->scale;
        }

        if(newWidth < lineWidth)
            newWidth = lineWidth;

        newHeight += maxHeight;
        newHeight += margin;
    }
    newWidth += 20;
    width = newWidth;
    height = newHeight;
}

void Window::realignElements(){
    int y = posY + 10;

    for (std::list<UIElement*>* l : contents){
        int xLAlign = posX + 10 + margin;
        int xRAlign = posX + width - 10 - margin*2;
        int xCAlaign = posX + (width - listElementWidth(l))/2 + margin;
        int maxHeight = 0;
        y += margin;
        for (UIElement* elem : *l){
            if(elem->alignment == Alignment::Left){
                elem->setPosition(xLAlign, elem->posY);
                xLAlign += (elem->width + margin);
            }
            if(elem->alignment == Alignment::Center){
                elem->setPosition(xCAlaign, elem->posY);
                xCAlaign += (elem->width + margin);
            }
            if(elem->alignment == Alignment::Right){
                elem->setPosition(xRAlign - elem->width, elem->posY);
                xRAlign -= (elem->width + margin);
            }
            if(elem->height > maxHeight){
                maxHeight = elem->height;
            }
            elem->setPosition(elem->posX, y);
        }
        y += maxHeight;
    }

}

void Window::updatePos(){
    shadow->width = width;
    shadow->height = height;
    shadow->posX = posX + 10;
    shadow->posY = posY + 10;;
    background->width = width;
    background->height = height;
    background->posX = posX;
    background->posY = posY;
    frameBottom->width = width-16;
    frameBottom->height = height-16;
    frameBottom->posX = posX + 8;
    frameBottom->posY = posY + 8;
    frameTop->width = width-20;
    frameTop->height = height-20;
    frameTop->posX = posX + 10;
    frameTop->posY = posY + 10;
}

void Window::flipColors(){
    shadow->textureColor  = {240,240,240};
    background->textureColor = {10,10,10};
    frameBottom->textureColor = {240,240,240};
    frameTop->textureColor = {10,10,10};
     for (std::list<UIElement*>* l : contents){
        for (UIElement* elem : *l){
            if (Button* btn = dynamic_cast<Button*>(elem)) {
                btn->shadow->textureColor = {255,255,255};
                btn->background->textureColor = {20,20,20};
                btn->label->textColor = {255,255,255};
                btn->label->setText(btn->label->text);
		    }
		    else if (Label* lbl = dynamic_cast<Label*>(elem)){
                
		    }
        }
        
    }
}

int Window::listElementWidth(std::list<UIElement*>* list){
    int width = margin*2;
    for (UIElement* elem : *list){
            width += elem->width*elem->scale + margin;
        }
    return width;
}