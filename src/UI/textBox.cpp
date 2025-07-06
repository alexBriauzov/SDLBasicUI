#include "TextBox.h"

TextBox::TextBox(int x, int y, int w, int h): UIElement(x, y){
	background = new Image(x, y, w, h, "assets/white.png");
	background->setLayer(0);

    label = new Label(x + 10, y + 10, "Label");
	label->setLayer(1);
	children.push_front(background);
    children.push_front(label);
	blocksMouseTracing = false;

}

TextBox::~TextBox(){
}


void TextBox::playText(std::string text){
    textString = text;
    currentTextString = "";
	label->setText(currentTextString);
    needsUpdate = true;
    lastUpdateTick = 0;
}

void TextBox::setText(std::string text){
	label->setText(text);
}

void TextBox::update(long long tick){
    if(lastUpdateTick + 20 >= tick){
        return;
    }
    if(currentTextString.length() == textString.length()){
        needsUpdate = false;
        return;
    }
    lastUpdateTick = tick;
    currentTextString = textString.substr(0, currentTextString.length() + 1);
    setText(currentTextString);

}