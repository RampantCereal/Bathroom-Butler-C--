#include "playStage.h"

playStage::playStage()
{	
}

void playStage::update(double seconds_elapsed, world* world) {
	float time; 

	//timer for npc
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			if (world->npcPositions[i+j*3].activeState == true){
				time = world->npcPositions[i + j * 3].npcTimer -seconds_elapsed;
				if (time<=0) {
					world->getPlayer()->reduceHealth();
					world->deactivateNPC(i, j);
				}
				world->npcPositions[i + j * 3].npcTimer = time;
			}
		}
	}

	//bathroom timers
	if (world->shower.busy) {
		world->shower.bathroomTimer -= seconds_elapsed;
		if (world->shower.bathroomTimer <= 0){
			world->shower.busy = false;
		}
	}
	if (world->makeup.busy) {
		world->makeup.bathroomTimer -= seconds_elapsed;
		if (world->makeup.bathroomTimer <= 0) {
			world->makeup.busy = false;
		}
	}

	//spawn of npcs
	spawnTimer += seconds_elapsed;
	if (spawnTimer >= 8) {
		canSpawn = true;
	}
	if (canSpawn) {

		world->activateNPC(world->npcToSpawn);
		spawnTimer = 0;
		canSpawn = false;
	}

	
	//level timer
	time= world->getTimer() - seconds_elapsed;
	
	world->setTimer(time);

	

	if ( world->getPlayer()->getHealth() <= 0) {
		Game::instance->nextStage();
	}
	else if (time <= 0 || Input::wasKeyPressed(SDL_SCANCODE_N)) {
		world->initWorld(60,world->getScore(),world->level +1, false);
	}


	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key up
	{

		if (world->npcPositions[world->getPlayer()->getCursorPos() + 3 * world->getPlayer()->getPosition()].activeState == true && world->shower.busy == true) {
			//move door and busy sound
			Game::instance->synth.playSample("data/busy.wav", 1, false);
		}
		else if(world->npcPositions[world->getPlayer()->getCursorPos()+3* world->getPlayer()->getPosition()].activeState == true && world->shower.busy == false ){
			if (world->npcPositions[world->getPlayer()->getCursorPos() + 3 * world->getPlayer()->getPosition()].type == 2) {

				world->deactivateNPC(world->getPlayer()->getCursorPos(), world->getPlayer()->getPosition());
				world->getPlayer()->reduceHealth();
				//negative sound
				Game::instance->synth.playSample("data/negative.wav", 1, false);
			}
			else {
				world->deactivateNPC(world->getPlayer()->getCursorPos(), world->getPlayer()->getPosition());
				//positive sound
				Game::instance->synth.playSample("data/positive.wav", 1, false);

				world->increaseScore(50);
				world->shower.busy = true;

				switch (world->npcPositions[world->getPlayer()->getCursorPos() + 3 * world->getPlayer()->getPosition()].type) {
				case 0:
					world->shower.bathroomTimer = 4;
					break;
				case 1:
					world->shower.bathroomTimer = 8;
					break;
				}
			}
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_X)) //if key up
	{
		if (world->npcPositions[world->getPlayer()->getCursorPos() + 3 * world->getPlayer()->getPosition()].activeState == true && world->makeup.busy == true) {
			//move door and busy sound
			Game::instance->synth.playSample("data/busy.wav", 1, false);
		}
		else if (world->npcPositions[world->getPlayer()->getCursorPos() + 3 * world->getPlayer()->getPosition()].activeState == true && world->makeup.busy == false) {
			if (world->npcPositions[world->getPlayer()->getCursorPos() + 3 * world->getPlayer()->getPosition()].type == 1) {

				world->deactivateNPC(world->getPlayer()->getCursorPos(), world->getPlayer()->getPosition());
				world->getPlayer()->reduceHealth();
				//negative sound
				Game::instance->synth.playSample("data/negative.wav", 1, false);
			}
			else {
				world->deactivateNPC(world->getPlayer()->getCursorPos(), world->getPlayer()->getPosition());
				//positive  sound
				Game::instance->synth.playSample("data/positive.wav", 1, false);

				world->increaseScore(50);
				world->makeup.busy = true;

				switch (world->npcPositions[world->getPlayer()->getCursorPos() + 3 * world->getPlayer()->getPosition()].type) {
				case 0:
					world->makeup.bathroomTimer = 4;
					break;
				case 2:
					world->makeup.bathroomTimer = 6;
					break;
				}
			}
		}

	}
	if (Input::wasKeyPressed(SDL_SCANCODE_UP) && world->getPlayer()->getPosition() != 0) //if key up
	{
		world->getPlayer()->setPosition(0);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN) && world->getPlayer()->getPosition() != 1) //if key down
	{
		world->getPlayer()->setPosition(1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_LEFT) && world->getPlayer()->getCursorPos() != 0) //if key up
	{
		world->getPlayer()->moveCursor(-1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RIGHT) && world->getPlayer()->getCursorPos() != 2) //if key up
	{
		world->getPlayer()->moveCursor(1);
	}
	// debug
	if (Input::wasKeyPressed(SDL_SCANCODE_D)) {
		world->getPlayer()->reduceHealth();
	}
}


void playStage::render(Image* fb, Image font, world* world) {
	//Background
	fb->drawImage(*Image::Get("data/bg.tga"),0,0);

	fb->drawText(std::to_string((int)(world->getTimer())), 0, 0, font);// print time left in seconds

	//draw health
	for (int i = 0; i < world->getPlayer()->getHealth(); i++) {
		fb->drawImage(*Image::Get("data/heart.tga"), 44 + 12 * i, 120);
	}
	//draw points
	fb->drawText(std::to_string(world->getScore()),64,0,font);//only 9 numbers fit with this font
	

	//1st floor door
	fb->drawImage(*Image::Get("data/door_shower.tga"),0, 16 * 2-1);
	if (world->shower.busy) {
		fb->drawText(std::to_string((int)(world->shower.bathroomTimer)), 0, 16 - 1, font);// print time left in seconds
	}
	//ground floor door
	fb->drawImage(*Image::Get("data/door_makeup.tga"), 0, 16 * 5-1);
	if (world->makeup.busy) {
		fb->drawText(std::to_string((int)(world->makeup.bathroomTimer)), 0, 16 - 1 + 16*3, font);// print time left in seconds
	}

	//draw npc
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			if (world->npcPositions[i+j*3].activeState) {
				switch (world->npcPositions[i + j * 3].type) {
					case 0:
						if ((int)(Game::instance->time) % 2 == 0) {
							fb->drawImage(*Image::Get("data/piss1.tga"), 48 + i * (80 / 3), 16 * (2 + j * 3));
						}
						else {
							fb->drawImage(*Image::Get("data/piss2.tga"), 48 + i * (80 / 3), 16 * (2 + j * 3));
						}
						break;
						break;
					case 1:
						if ((int)(Game::instance->time) % 2 == 0) {
							fb->drawImage(*Image::Get("data/stink1.tga"), 48 + i * (80 / 3), 16 * (2 + j * 3));
						}
						else {
							fb->drawImage(*Image::Get("data/stink2.tga"), 48 + i * (80 / 3), 16 * (2 + j * 3));
						}
						break;
					case 2:
						fb->drawImage(*Image::Get("data/haircut.tga"), 48 + i * (80 / 3), 16 * (2 + j * 3));
						break;

				}
				
				fb->drawText(std::to_string((int)(world->npcPositions[i + j * 3].npcTimer)), 48 + i * (80 / 3), 16+j*3*16, font);// print time left in seconds
			}
		}
	}

	//draw player character
	if ((int)(Game::instance->time)%8 == 0) {
		fb->drawImage(*Image::Get("data/main_center.tga"), 48 - 1 * (80 / 3), 16 * 2 + world->getPlayer()->getPosition() * 16 * 3);
	}
	else {
		fb->drawImage(*Image::Get("data/main_left.tga"), 48 - 1 * (80 / 3), 16 * 2 + world->getPlayer()->getPosition() * 16 * 3);
	}
	//draw level number
	fb->drawText("L:"+std::to_string(world->level), 0, 120, font);

	//cursor
	fb->drawImage(*Image::Get("data/cursor.tga"), -5 * pow(sin(Game::instance->time), 2) + (64 + world->getPlayer()->getCursorPos() * (80 / 3)), 16 * (2 + world->getPlayer()->getPosition() * 3) + 8);
	
	//level indicator
	if ((int)world->getTimer()%59 == 0) {
		fb->drawText("LEVEL: " + std::to_string(world->level), 64-4*7, 64-9, font);
	}
	
}

