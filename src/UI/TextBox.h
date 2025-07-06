#pragma once
#include "UIElement.h"
#include "Image.h"
#include "Label.h"

class TextBox: public UIElement
{
public:

    virtual ~TextBox();

    Image* background;
    Label* label;

    TextBox(int posX, int posY, int width, int height);

    void playText(std::string text);

    void setText(std::string text);

    void update(long long tick) override;

private:

    long long lastUpdateTick;

    std::string textString;
    std::string currentTextString;
};