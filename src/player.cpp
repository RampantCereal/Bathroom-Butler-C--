#include "player.h"

int health;
int position;
int cursorPos;

player::player()
{	
	player::init();
}

void player::init() {
	health = 3;
	position = 0;
	cursorPos = 0;
	
}

int player::getHealth() {
	return health;
}

void player::reduceHealth() {
	health--;
	Game::instance->synth.playSample("data/hit.wav", 1, false);
}

int player::getPosition() {
	return position;
}

void player::setPosition(int newPos) {
	position = newPos;
	Game::instance->synth.playSample("data/moveCursor.wav", 1, false);
}

void player::moveCursor(int direction) {// input is 1 or -1
	cursorPos = (cursorPos + direction) % 3;
	Game::instance->synth.playSample("data/moveCursor.wav", 1, false);
}

int player::getCursorPos() {
	return cursorPos;
}




