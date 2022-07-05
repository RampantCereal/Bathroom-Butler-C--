#ifndef STAGE_H
#define STAGE_H


#include "world.h"
#include "image.h"
#include "input.h"
#include "game.h"

class stage
{
public:
	stage();
	virtual void update(double dt, world* world);
	virtual void render(Image* framebuffer, Image font, world* world);
};

#endif