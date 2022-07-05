#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"
#include "menuStage.h"
#include "introStage.h"
#include "playStage.h"
#include "endStage.h"
#include "world.h"


#include <cmath>

Game* Game::instance = NULL;

float maxTime = 60; //max time in secoonds for the playLevel

Image font;
Image minifont;
Image sprite;
Color bgcolor(130, 80, 100);
stage* current_stage = NULL;
menuStage* mainMenu = new menuStage();
introStage* intro = new introStage();
playStage* play = new playStage();
endStage* ending = new endStage();
world* worldState = new world(maxTime);
float volumeIntro, volumePlay, volumeEnd;
//int stageN = 0;//from 0 to 3, marks the stage that is active, 0 is main menu, 1 in intro, 2 is play, 3 is ending

Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	stageN = 0;

	font.loadTGA("data/bitmap-font-white.tga"); //load bitmap-font image
	minifont.loadTGA("data/mini-font-white-4x6.tga"); //load bitmap-font image
	//sprite.loadTGA("data/spritesheet.tga"); //example to load an sprite

	enableAudio(); //enable this line if you plan to add audio to your application
	//music
	//synth.playSample("data/intro.wav", 0,true);
	synth.playSample("data/play.wav", 1, true);
	//synth.playSample("data/end.wav", 1, true);
	//synth.osc1.amplitude = 0.5;
	current_stage = mainMenu;
	srand(GetTickCount());

	
	
}

//what to do when the image has to be draw
void Game::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer(128, 128); //do not change framebuffer size

	//add your code here to fill the framebuffer
	//...
	current_stage->render(&framebuffer, font, worldState);
	//some new useful functions
		//framebuffer.fill( Color(255,0,0) );								//fills the image with one color
		//framebuffer.drawLine( 0, 0, 100,100, Color::RED );		//draws a line
		//framebuffer.drawImage( sprite, 0, 0 );					//draws full image
		//framebuffer.drawImage( sprite, 0, 0, 128, 128 );			//draws a scaled image
		//framebuffer.drawImage( sprite, 0, 0, Area(0,0,14,18) );	//draws only a part of an image
		//framebuffer.drawText( "Hello World", 0, 0, font );				//draws some text using a bitmap font in an image (assuming every char is 7x9)
		//framebuffer.drawText( toString(time), 1, 10, minifont,4,6);	//draws some text using a bitmap font in an image (assuming every char is 4x6)
	
	//send image to screen
	showFramebuffer(&framebuffer);
}

void Game::update(double seconds_elapsed)
{
	//Add here your update method
	//...
	current_stage->update(seconds_elapsed,worldState);

	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key left
	{
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key right
	{
		
	}

	//example of 'was pressed'
	if (Input::wasKeyPressed(SDL_SCANCODE_X)) //if key A was pressed
	{
		
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_R)) //if key R was pressed
	{
		stageN = 0;
		current_stage = mainMenu; // universal reset
	}

	//to read the gamepad state
	if (Input::gamepads[0].isButtonPressed(A_BUTTON)) //if the A button is pressed
	{
	}

	if (Input::gamepads[0].direction & PAD_UP) //left stick pointing up
	{
		bgcolor.set(0, 255, 0);
	}
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseMove(SDL_MouseMotionEvent event)
{
}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	window_width = width;
	window_height = height;
}

//sends the image to the framebuffer of the GPU
void Game::showFramebuffer(Image* img)
{
	static Image finalframe;

	if (window_width < img->width * 4 || window_height < img->height * 4)
	{
		finalframe = *img;
		finalframe.scale( window_width, window_height );
	}
	else
	{
		if (finalframe.width != window_width || finalframe.height != window_height)
		{
			finalframe.resize(window_width, window_height);
			finalframe.fill(Color::BLACK);
		}
		finalframe.drawImage(*img, (window_width - img->width * 4) * 0.5, (window_height - img->height * 4) * 0.5, img->width * 4, img->height * 4);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (1) //flip
	{
		glRasterPos2f(-1, 1);
		glPixelZoom(1, -1);
	}

	glDrawPixels(finalframe.width, finalframe.height, GL_RGBA, GL_UNSIGNED_BYTE, finalframe.pixels);
}

//AUDIO STUFF ********************

SDL_AudioSpec audio_spec;

void AudioCallback(void*  userdata,
	Uint8* stream,
	int    len)
{
	static double audio_time = 0;

	memset(stream, 0, len);//clear
	if (!Game::instance)
		return;

	Game::instance->onAudio((float*)stream, len / sizeof(float), audio_time, audio_spec);
	audio_time += len / (double)audio_spec.freq;
}

void Game::enableAudio()
{
	SDL_memset(&audio_spec, 0, sizeof(audio_spec)); /* or SDL_zero(want) */
	audio_spec.freq = 48000;
	audio_spec.format = AUDIO_F32;
	audio_spec.channels = 1;
	audio_spec.samples = 1024;
	audio_spec.callback = AudioCallback; /* you wrote this function elsewhere. */
	if (SDL_OpenAudio(&audio_spec, &audio_spec) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_PauseAudio(0);
}

void Game::onAudio(float *buffer, unsigned int len, double time, SDL_AudioSpec& audio_spec)
{
	//fill the audio buffer using our custom retro synth
	synth.generateAudio(buffer, len, audio_spec);
}

//change current stage

void Game::nextStage() {
	int stageID = (Game::instance->stageN + 1) % 4;

	switch (stageID) {
	case 0:
		synth.playSample("data/next.wav", 1, false);
		current_stage = mainMenu;
		Game::instance->stageN = stageID;
		break;
	case 1:
		synth.playSample("data/next.wav", 1, false);
		current_stage = intro;
		Game::instance->stageN = stageID;
		break;
	
	case 2:
		synth.playSample("data/next.wav", 1, false);
		worldState->initWorld(maxTime, 0,1, true);
		current_stage = play;
		Game::instance->stageN = stageID;
		break;
	case 3:
		synth.playSample("data/fail.wav", 1, false);
		current_stage = ending;
		Game::instance->stageN = stageID;
		break;
	}
}

