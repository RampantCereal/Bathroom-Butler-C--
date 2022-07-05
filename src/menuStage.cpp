#include "menuStage.h"



menuStage::menuStage()
{	
}

void menuStage::update(double seconds_elapsed, world* world) {
	if (Input::wasKeyPressed(SDL_SCANCODE_X)){ //if key A was pressed
		
		Game::instance->nextStage();
		
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)){ //if key Z was pressed
		
		Game::instance->nextStage();
		
	}
	
}
void menuStage::render(Image* framebuffer, Image font, world* world) {
	//framebuffer->fill(Color(0, 0, 255));
	framebuffer->drawImage(*Image::Get("data/menuBG.tga"), 0, 0);
	framebuffer->drawText("Bathroom Butler", 0, 0, *Image::Get("data/bitmap-font-black.tga"));
	framebuffer->drawLine(0, 8, 7 * 15, 8, Color::BLACK);
	framebuffer->drawText("Press Z or X", 15*sin(Game::instance->time)+22, 2*sin(Game::instance->time)+70, *Image::Get("data/bitmap-font-black.tga"));
	
}
