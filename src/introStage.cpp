#include "introStage.h"

introStage::introStage()
{	
}

void introStage::update(double seconds_elapsed, world* world) {
	if (Input::wasKeyPressed(SDL_SCANCODE_X)) { //if key A was pressed

		Game::instance->nextStage();

	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) { //if key Z was pressed

		Game::instance->nextStage();

	}
}
void introStage::render(Image* framebuffer, Image font, world* world) {
	//std::cout << "pleaseworks" << std::endl;
	framebuffer->fill(Color(0, 0, 0));
	framebuffer->drawText("Bathroom Butler", 0, 0, font);
	framebuffer->drawLine(0, 8, 7 * 15, 8, Color::WHITE);

	framebuffer->drawText("Administra la cola del lavabo", 0, 16, *Image::Get("data/mini-font-white-4x6.tga"),4,6);
	framebuffer->drawText("si no quieres perder tu trabajo!", 0, 16 +5, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);

	framebuffer->drawText("Cursores: seleccionar personajes", 0, 16 + 15, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);

	framebuffer->drawText("Z: si apestan, a la ducha", 0, 16 + 30, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);

	framebuffer->drawText("X: para mandarlos a arreglarse", 0, 16 + 45, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);

	framebuffer->drawText("si tienen otras necesidades,los", 0, 16 + 60, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);
	framebuffer->drawText("puedes mandar a qualquier lavabo", 0, 16 + 60+5, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);

	framebuffer->drawText("cuidado, si los mandas a donde", 0, 16 + 75, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);
	framebuffer->drawText("no toca, presentaran una queja", 0, 16 + 75+5, *Image::Get("data/mini-font-white-4x6.tga"), 4, 6);

	framebuffer->drawText("Press Z or X", 15 * sin(Game::instance->time) + 22, 110, font);
}
