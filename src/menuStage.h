#ifndef MENUSTAGE_H
#define MENUSTAGE_H


#include "stage.h"

class menuStage : public stage
{
public:
	menuStage();
	virtual void render(Image* framebuffer, Image font, world* world);
	virtual void update(double seconds_elapsed, world* world);
};

#endif