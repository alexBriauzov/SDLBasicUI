#pragma once
#include "UIElement.h"
#include "Image.h"
#include "Label.h"
#include "Button.h"
#include <list>
#include <string>


class Window
{
public:
    int width;
    int height;
    int posX;
    int posY;
    int layer;
    int margin;

    // UIElemnts contained within the window. Placed from top to bottom
    // each internal lists represents a list aligned horizontally
    std::list<std::list<UIElement*>*> contents;

    Window(int width, int height, int layer);
    virtual ~Window();

    // display the window
    void open();

    // delete window and its elements
    void close();

    // add a text element to the window
    // alignment is either Left, Center or Right
    // if newLine is false then this element will be added to the right of the last one
    UIElement* addText(std::string text, Alignment alignment, bool newLine);

    // add an image element to the window
    // alignment is either Left, Center or Right
    // if newLine is false then this element will be added to the right of the last one
    UIElement* addImage(std::string textureTag, Alignment alignment, bool newLine);

    // add a button element to the window
    // alignment is either Left, Center or Right
    // if newLine is false then this element will be added to the right of the last one
    UIElement* addButton(std::string text, std::string textureTag, Alignment alignment, bool newLine);

    // automatically resize the window to fit all elements it contains
    void autoResize();

    // realign uiElements
    void realignElements();

    // realign position and width
    void updatePos();

    // change from blackOnWhite to WhiteOnBlack
    void flipColors();

    // calculates the combined width of elements in the list with margins
    int listElementWidth(std::list<UIElement*>* list);


private:
    Image* shadow = NULL;
    Image* background = NULL;
    Image* frameBottom = NULL;
    Image* frameTop = NULL;
};