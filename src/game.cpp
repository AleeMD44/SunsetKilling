#include "game.h"
#include <cmath>


//some globals
Game* Game::instance = NULL;

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
	mouse_locked = true;
	pause_inside_game = false;
	tutorial_done = false;
	//OpenGL flags
	glEnable(GL_CULL_FACE); //render both sides of every triangle
	glEnable(GL_DEPTH_TEST); //check the occlusions using the Z buffer

	//create our camera
	new MenuStage(window_width, window_height);
	new PauseStage(window_width, window_height);
	new OptionStage(window_width, window_height);
	new WinLoseStage(window_width, window_height);
	new TutorialStage(window_width, window_height);
	new PlayStage();


	BASS_Init(-1, 44100, 0, 0, NULL);
	BASS_SetVolume(1);
	bass = new Bass();
	bass->getChannel("data/sounds/background.mp3");
	bass->getChannel("data/sounds/lofitest2.mp3");
	bass->getChannel("data/sounds/car.mp3");
	bass->getChannel("data/sounds/walking.mp3");
	bass->getChannel("data/sounds/running.mp3");
	bass->getChannel("data/sounds/gather.mp3");
	bass->getChannel("data/sounds/dead.mp3");
	bass->getChannel("data/sounds/phonein.mp3");
	bass->getChannel("data/sounds/phoneout.mp3");
	bass->getChannel("data/sounds/hit1.mp3");
	bass->getChannel("data/sounds/hit2.mp3");
	bass->getChannel("data/sounds/hit3.mp3");
	bass->getChannel("data/sounds/hit4.mp3");
	bass->getChannel("data/sounds/money.mp3");
	bass->playChannel("data/sounds/background.mp3", 0.1, true);

	scene = new Scene(window_width, window_height);

	//hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
}

//what to do when the image has to be draw
void Game::render(void)
{
	Stage::current_stage->render();
	//Draw the floor grid
	//drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);


	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	Stage::current_stage->update(seconds_elapsed);

	if (mouse_locked)
		Input::centerMouse();
}

//Keyboard event handler (sync input)
void Game::onKeyDown(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
		//case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	case SDLK_F1: Shader::ReloadAll(); break;
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

void Game::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}
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
	glViewport(0, 0, width, height);
	scene->camera->aspect = width / (float)height;
	window_width = width;
	window_height = height;
}

