#ifndef PLAYSTAGE_H
#define PLAYSTAGE_H


#include "stage.h"
class playStage : public stage
{
public:
	playStage();
	virtual void render(Image* framebuffer, Image font, world* world);
	virtual void update(double seconds_elapsed, world* world);
private:
	bool canSpawn = true;
	float spawnTimer = 0;
};

#endif