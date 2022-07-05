#include "npc.h"



npc::npc()
{
	
	activeState = false;
	
}

float npc::getTimer() {
	return npcTimer;
}
void npc::setTimer(float time) {
	npcTimer = time;
}

bool npc::getState() {
	return activeState;
}

void npc::setState(bool newState) {
	activeState = newState;
}


