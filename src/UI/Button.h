#pragma once
#include "UIElement.h"
#include "Image.h"
#include "Label.h"

class Button: public UIElement
{
public:

    virtual ~Button();

    Image* shadow;
    Image* background;
    Label* label;

    Button(int posX, int posY, int width, int height, std::string textureTag);

    Button(int posX, int posY, std::string textureTag, std::string text);

private:

    static bool onElementLeftClickDefault(UIElement* element);
    static bool onElementRightClickDefault(UIElement* element);
    static bool onElementEnterDefault(UIElement* element);
    static bool onElementExitDefault(UIElement* element);

};