#ifndef PlAYER_H
#define PLAYER_H
#include "game.h";

class player
{
public:
	player();
	int getHealth();
	void init();
	int getPosition();
	void setPosition(int newPos);
	void reduceHealth();
	void moveCursor(int direction);
	int getCursorPos();
};


#endif