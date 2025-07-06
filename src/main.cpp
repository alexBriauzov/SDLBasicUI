#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include <iostream>
#include <chrono>
#include <SDL_ttf.h>
#include "UIElement.h"
#include "Animation.h"
#include "Image.h"
#include "Label.h"
#include "TextureManager.h"
#include "Button.h"
#include "Window.h"

SDL_Window* window;
SDL_Renderer* renderer;
bool isRunning;
long long tick;

long long getCurrentTime(){
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

UIElement* getUIElementAtXY(int x, int y) {
	for (std::list<UIElement*>::reverse_iterator i = UIElement::uiList.rbegin(); i != UIElement::uiList.rend(); ++i)
		if ((*i)->blocksMouseTracing && (*i)->posX <= x && (*i)->posX + (*i)->width > x &&
			(*i)->posY <= y && (*i)->posY + (*i)->height > y)
			return (*i);
	return NULL;
}

void update(){
	// get time
	tick = getCurrentTime();

	//check to see if mouse moved since last frame

	int newMouseX; int newMouseY;
	SDL_GetMouseState(&newMouseX,&newMouseY);

	// check if the cursor is pointing at some UI element on this frame
	UIElement* e = getUIElementAtXY(newMouseX, newMouseY);

	if(UIElement::tagetedElement != e && UIElement::tagetedElement != NULL && UIElement::tagetedElement->onExit != NULL){
		UIElement::tagetedElement->onExit(UIElement::tagetedElement);
	}

	if(UIElement::tagetedElement != e && e != NULL && e->onEnter != NULL){
		e->onEnter(e);
	}
	
	UIElement::tagetedElement = e;

	SDL_Event ev;

	while (SDL_PollEvent(&ev)){
		switch (ev.type)
		{
		case SDL_QUIT:
			isRunning = false;
		break;

		case SDL_MOUSEBUTTONUP:
			//Left button released
			if(ev.button.button == SDL_BUTTON_LEFT){
				if(UIElement::tagetedElement != NULL && UIElement::tagetedElement->onLClick != NULL){
					UIElement::tagetedElement->onLClick(UIElement::tagetedElement);
				}
			}
			//Right button released
			if(ev.button.button == SDL_BUTTON_RIGHT){
				if(UIElement::tagetedElement != NULL && UIElement::tagetedElement->onRClick != NULL){
					UIElement::tagetedElement->onRClick(UIElement::tagetedElement);
				}
			}

		break;

		case SDL_MOUSEBUTTONDOWN:
			//Right button pressed
			if(ev.button.button == SDL_BUTTON_LEFT){
				// add if needed
			}
		break;

		default:
			break;
		}
	}

	for (Animation* anim : Animation::animationList) {
		if(anim->isPlaying){
			anim->update(anim);
		}
	}

	Animation::animationList.remove_if([](Animation* anim){ return anim->isFinished; });

}

void render(){
	SDL_RenderClear(renderer);

	UIElement::sortElements();
	
	for (UIElement* elem : UIElement::uiList) {
		if(elem->needsUpdate){
			elem->update(tick);
		}

		if (Image* img = dynamic_cast<Image*>(elem)) {
			SDL_Rect chunk = {img->frameOffsetX,img->frameOffsetY,img->width,img->height};
			SDL_Rect frame;
			frame.x = img->posX;
			frame.y = img->posY;
			frame.w = img->width*img->scale;
			frame.h = img->height*img->scale;
			SDL_Texture* tex = TextureManager::getTexture(img->texture);
			SDL_SetTextureColorMod(tex, 
				img->textureColor.r*img->textureColorMult,
				img->textureColor.g*img->textureColorMult,
				img->textureColor.b*img->textureColorMult);
			SDL_SetTextureAlphaMod(tex, img->opacity*255);
			SDL_RenderCopy(renderer, tex, &chunk, &frame);
			SDL_SetTextureColorMod(tex, 255, 255, 255);
			SDL_SetTextureAlphaMod(tex, 255);
		}
		else if (Label* lbl = dynamic_cast<Label*>(elem)){
			SDL_Rect frame;
			frame.x = elem->posX;
			frame.y = elem->posY;
			frame.w = elem->width*lbl->scale;
			frame.h = elem->height*lbl->scale;
			SDL_RenderCopy(renderer, lbl->textTexture, NULL, &frame);
		}
	}
	
	SDL_RenderPresent(renderer);
}


int main(int argv, char** args) {

	// initialize SDL graphic stuff
    SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	// create the window and SDL renderer
	window = SDL_CreateWindow( "PrSc", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 900, SDL_WINDOW_ALLOW_HIGHDPI );
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TextureManager::renderer = renderer;

	// load some different font sizes
	Label::font60 = TTF_OpenFont("assets/Inconsolata.ttf",60);
	Label::font45 = TTF_OpenFont("assets/Inconsolata.ttf",45);
	Label::font30 = TTF_OpenFont("assets/Inconsolata.ttf",30);
    // load textures
	TextureManager::loadTexture("assets/white.png", 0, 0);
	TextureManager::loadTexture("assets/cigcat.png", 0, 0);

	// create a background image of gray color
	Image* bck = new Image(0, 0, 1200, 900, "assets/white.png");
	bck->textureColor = {50, 50, 50};
	bck->setLayer(-999);

	// create an image at x=100, y=100 of size 341x323 pixels
	Image* img = new Image(100, 100, 683, 647, "assets/cigcat.png");
	img->scale = 0.5;
	img->setLayer(1);

	// create an label at x=100, y=50 with pink color and font size 30
	Label* lbl = new Label(100, 50, "text that will be overwritten in the next lines");
	lbl->setTextFontSize(30);
	lbl->textColor = {255, 200, 200};
	lbl->setText("do what you want, want what you do"); // have to call setText() for setTextFontSize() and textColor to take effect
	lbl->setLayer(1);

	// create an button at x=500, y=300
	Button* btn = new Button(700, 200, "assets/white.png", " button ");
	btn->setLayer(1);

	// create a window with a button centered on top and different labels below
	Window* wnd = new Window(10, 10, 1);
	wnd->posX = 50;
	wnd->posY = 500;
	wnd->addButton("window button", "assets/white.png", Alignment::Center, true);
	wnd->addText("Label 1", Alignment::Center, true);
	wnd->addText("Label 2", Alignment::Left, true);
	wnd->addText("Label 3", Alignment::Right, true);
	wnd->addText(" A very long label ", Alignment::Center, true);
	wnd->addText(" A label right next to it ", Alignment::Center, false);
	wnd->addImage("assets/white.png", Alignment::Center, true);
	wnd->autoResize();
	wnd->realignElements();
	wnd->open();
	

	// benchmarking variables for the fps counter
	long long lastUpdateDuration = 0;
	long long lastRenderDuration = 0;
	long long lastCallDuration = 0;
	long long callStart = 0;
	long long lastCall = 0;
	int renderCallCounter = 0;
	isRunning = true;
	int fpsTarget = 60;

	// main loop calls update(); and render();
	while (isRunning) {
		if(1000/fpsTarget <= lastCallDuration){
			SDL_Delay(1);
		} else {
			SDL_Delay(1000/fpsTarget - lastCallDuration);
		}
		callStart = getCurrentTime();
		if(callStart/1000 > lastCall/1000){
		lastCall = callStart;
		std::cout<<"fps:"<<renderCallCounter<< " " << lastUpdateDuration << " " << lastRenderDuration << "ms\n";
		renderCallCounter = 0;
		}
		renderCallCounter++;
		update();
		lastUpdateDuration = getCurrentTime() - callStart;
		render();
		lastRenderDuration = getCurrentTime() - callStart - lastUpdateDuration;
		lastCallDuration = getCurrentTime() - callStart;
	}

	// if no longer running deinitialize and exit
	std::cout<<"quitting...\n";
	TTF_Quit();
	SDL_Quit();	

return 0;
}