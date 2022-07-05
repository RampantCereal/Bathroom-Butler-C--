#include "stage.h"


stage::stage()
{
}

void stage::update(double seconds_elapsed, world* world) {
	std::cout << "calling update on base class" << std::endl;
}
void stage::render(Image* framebuffer, Image font, world* world) {
	std::cout << "calling render on base class" << std::endl;
}


