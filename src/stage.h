/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#ifndef STAGE_H
#define STAGE_H

#include "includes.h"
#include "camera.h"
#include "utils.h"
#include "car.h"
#include "player.h"
#include "mesh.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"
#include "animation.h"
#include "entity.h"

class Stage
{
public:

	static std::map<std::string, Stage*> s_stages;
	static Stage* current_stage;

	static void changeStage(const char* name);

	Stage(const char* name);

	virtual void render();
	virtual void update(double seconds_elapsed);

};


class PlayStage : public Stage {

public:

	//some vars
	Camera* camera; //our global camera

	PlayStage() : Stage("play") {}



	//main functions
	void render(void);
	void update(double seconds_elapsed);

};

class MenuStage : public Stage {

public:

	//some vars
	Camera* camera; //our global camera
	int selector = 1;
	Mesh* quad;
	Mesh* quad2;

	MenuStage(int window_width, int window_height) : Stage("menu") {
		quad = new Mesh();
		quad2 = new Mesh();
		camera = new Camera();
		camera->setOrthographic(0, window_width, window_height, 0, -1, 1);
		camera->setPerspective(90.f, window_width / (float)window_height, 0.1f, 10000.f);
		camera->enable();

	}

	//main functions
	void render(void);
	void update(double seconds_elapsed);

};

class PauseStage : public Stage {

public:

	//some vars
	Camera* camera; //our global camera
	int selector = 1;
	Mesh* quad;
	Mesh* quad2;

	PauseStage(int window_width, int window_height) : Stage("pause") {
		quad = new Mesh();
		quad2 = new Mesh();
		camera = new Camera();
		camera->setOrthographic(0, window_width, window_height, 0, -1, 1);
		camera->setPerspective(90.f, window_width / (float)window_height, 0.1f, 10000.f);
		camera->enable();

	}

	//main functions
	void render(void);
	void update(double seconds_elapsed);

};

class WinLoseStage : public Stage {

public:

	//some vars
	Camera* camera; //our global camera
	int selector = 1;
	Mesh* quad;
	Mesh* quad2;

	WinLoseStage(int window_width, int window_height) : Stage("winlose") {
		quad = new Mesh();
		quad2 = new Mesh();
		camera = new Camera();
		camera->setOrthographic(0, window_width, window_height, 0, -1, 1);
		camera->setPerspective(90.f, window_width / (float)window_height, 0.1f, 10000.f);
		camera->enable();

	}

	//main functions
	void render(void);
	void update(double seconds_elapsed);

};

class OptionStage : public Stage {

public:

	//some vars
	Camera* camera; //our global camera
	int selector = 1;
	int selector2 = 2;
	Mesh* quad;
	Mesh* quad2;

	OptionStage(int window_width, int window_height) : Stage("option") {
		quad = new Mesh();
		quad2 = new Mesh();
		camera = new Camera();
		camera->setOrthographic(0, window_width, window_height, 0, -1, 1);
		camera->setPerspective(90.f, window_width / (float)window_height, 0.1f, 10000.f);
		camera->enable();

	}

	//main functions
	void render(void);
	void update(double seconds_elapsed);

};

class TutorialStage : public Stage {

public:

	//some vars
	Camera* camera; //our global camera
	int selector = 1;
	int selector2 = 2;
	Mesh* quad;
	Mesh* quad2;

	TutorialStage(int window_width, int window_height) : Stage("tutorial") {
		quad = new Mesh();
		quad2 = new Mesh();
		camera = new Camera();
		camera->setOrthographic(0, window_width, window_height, 0, -1, 1);
		camera->setPerspective(90.f, window_width / (float)window_height, 0.1f, 10000.f);
		camera->enable();

	}

	//main functions
	void render(void);
	void update(double seconds_elapsed);

};

#endif 