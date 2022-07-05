#include "endStage.h"

endStage::endStage()
{	
}

void endStage::update(double seconds_elapsed, world* world) {
	if (Input::wasKeyPressed(SDL_SCANCODE_X)) { //if key A was pressed

		Game::instance->nextStage();

	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) { //if key Z was pressed

		Game::instance->nextStage();

	}
}
void endStage::render(Image* fb, Image font, world* world) {
	fb->fill(Color::BLACK);
	fb->drawText("FINAL SCORE :", 0, 0, font);
	fb->drawText(std::to_string(world->getScore()), 16, 8, font);

	fb->drawText("HIGHEST LEVEL :", 0, 25, font);
	fb->drawText(std::to_string(world->level), 16, 33, font);

	fb->drawText("JOB KEPT FOR :", 0, 50, font);
	fb->drawText(std::to_string((int)((60- world->getTimer())+60*(world->level -1))) +" s", 16, 58, font);

	fb->drawText("Press Z or X", 15 * sin(Game::instance->time) + 22, 90, font);
}
