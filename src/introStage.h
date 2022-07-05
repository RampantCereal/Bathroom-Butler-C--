#ifndef INTROSTAGE_H
#define INTROSTAGE_H


#include "stage.h"
class introStage : public stage
{
public:
	introStage();
	virtual void render(Image* framebuffer, Image font, world* world);
	virtual void update(double seconds_elapsed, world* world);
};

#endif