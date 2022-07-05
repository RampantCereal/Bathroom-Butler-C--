#ifndef WORLD_H
#define WORLD_H

#include "player.h"
#include "npc.h"
#include "bathroom.h"
#include <iostream>
#include <array>
class world
{
public:
	world(float maxTimer);
	float getTimer();
	void setTimer(float time);
	void initWorld(float maxTimer, int newScore, int newLevel, bool reset);
	player* getPlayer();
	void activateNPC(int npcN);
	void deactivateNPC(int x, int y);
	int getScore();
	void setScore(int value);
	void world::increaseScore(int score);
	npc npcPositions[6];
	bathroom shower;
	bathroom makeup;
	int npcToSpawn;
	int level;
	int maxScore;
private:
	float timer;
	int score;
	int maxNPC, npcCount;
	

};


#endif