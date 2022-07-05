#ifndef NPC_H
#define NPC_H
#include <stdlib.h>

class npc
{
public:
	npc();
	float getTimer();
	void setTimer(float time);
	bool getState();
	void setState(bool newState);
	float npcTimer = 10 + rand() % 5 - rand() % 5;
	int type;//0 = universal type 1 = only shower 2 = only makeup
	bool activeState = false;
};


#endif