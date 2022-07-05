#ifndef ENDSTAGE_H
#define ENDSTAGE_H


#include "stage.h"
class endStage : public stage
{
public:
	endStage();
	virtual void render(Image* framebuffer, Image font, world* world);
	virtual void update(double seconds_elapsed, world* world);
};

#endif