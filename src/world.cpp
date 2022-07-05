#include "world.h"




player* playerCharacter = new player();//player character, holds the position, health, sprite, cursor position
//posiciones de los NPC(matriz, dentro o fuera del player(world))
//bathroom (dos tipos), timer, is free


world::world(float maxTimer)
{	
	maxNPC = 6;

	
	world::initWorld(maxTimer, 0, 1, false);
	
}

float world::getTimer() {
	return timer;
}
void world::setTimer(float time) {
	timer = time;
}

int world::getScore(){
	return score;
}

void world::setScore(int value) {
	score = value;
}
void world::increaseScore(int addedScore) {
	score += addedScore;
}

player* world::getPlayer() {
	return playerCharacter;
}

void world::activateNPC(int npcN) {//activates npc at random in the scene
	int x,y;
	int temp = 0;
	
	//std::cout << "trying; x =" << x << "y =" << y <<" on " << npcPositions[x + 3 * y].activeState <<"\n";

	while (npcCount < maxNPC && temp < npcN) {
		x = (rand() % 3) ;
		y = (rand() % 2) ;
		int dice = (int)(rand() % 4);
		if (!npcPositions[x + 3 * y].activeState) {
			npcPositions[x + 3 * y].activeState = true;// needs to check limit
			npcCount++;
			temp++;
			npcPositions[x + 3 * y].npcTimer = 10 + rand() % 5 - rand() % 5;
			if (dice < 2) {
				npcPositions[x + 3 * y].type = 0;
			}
			else if (dice < 3 && dice >= 2) {
				npcPositions[x + 3 * y].type = 1;
			}
			else {
				npcPositions[x + 3 * y].type = 2;
			}
		}
		
		
	}
	
}

void world::deactivateNPC(int x, int y) {
	npcPositions[x + y * 3].activeState = false;
	npcCount--;
}

void world::initWorld(float maxTimer, int newScore, int newLevel, bool reset) {
	timer = maxTimer;
	playerCharacter->init();
	score = newScore;
	npcCount = 0;
	level = newLevel;
	if (reset) {
		npcToSpawn = 1;
	}
	if (npcToSpawn != 4) {
		npcToSpawn = level;
	}
	shower.busy = false;
	makeup.busy = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			if(npcPositions[i + 3 * j].activeState){
				npcPositions[i + 3 * j].activeState = false;
			}
		}
	}
	
}

