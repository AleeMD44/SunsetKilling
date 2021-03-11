#include "stage.h"
#include "game.h"
#include <cmath>

//some globals

void Stage::render() {}
void Stage::update(double seconds_elapsed) {}

void Stage::changeStage(const char* name)
{
	current_stage = s_stages[name];
}

Stage::Stage(const char* name) {
	s_stages[name] = this;
	if (current_stage == NULL)
		current_stage = this;
}

Stage* Stage::current_stage = NULL;
std::map<std::string, Stage*> Stage::s_stages;

void PlayStage::render(void)
{
	Game::instance->scene->render();
}

void PlayStage::update(double seconds_elapsed)
{
	Game::instance->scene->update(seconds_elapsed);

	if (Input::wasKeyPressed(SDL_SCANCODE_ESCAPE)) {

		changeStage("pause");
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_KP_PLUS)) {
		Game::instance->scene->myPlayer->money.carried += 1000;
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_KP_MINUS)) {
		Game::instance->scene->myPlayer->player.health -= 1;
	}
}
void restart() {
	Game::instance->scene->myCar->ourCar.acceleration_input = 0;
	Game::instance->scene->myCar->ourCar.front_vector = Vector3(0, 0, 1);
	Game::instance->scene->myCar->ourCar.entity->model.setIdentity();
	Game::instance->scene->myCar->ourCar.entity->model.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	Game::instance->scene->myCar->ourCar.entity->model.translate(0, 0.7, 0);
	Game::instance->scene->myCar->ourCar.position = Vector3(0, 0.7, 0);
	Game::instance->scene->myCar->ourCar.entity->model.scale(0.03, 0.03, 0.03);
	Game::instance->scene->myPlayer->player.entity->model.setIdentity();
	Game::instance->scene->myPlayer->player.angle = 90 * DEG2RAD;
	Game::instance->scene->myPlayer->player.position = Vector3(0, 0, 0);
	Game::instance->scene->myPlayer->player.health = 10;
	Game::instance->scene->myPlayer->player.entity->model.scale(0.15, 0.15, 0.15);
	Game::instance->scene->myPlayer->money.carried = 20;
	Game::instance->scene->car = true;
	Game::instance->scene->myPlayer->phone.moneypersecond = 0;
	for (int i = 0; i < Game::instance->scene->enemies.size(); i++) {
		Game::instance->scene->enemies[i]->player.state = LOST;
		Game::instance->scene->enemies[i]->money.carried = (rand() % 80) + 10;
		Game::instance->scene->enemies[i]->money.looted = false;
		Game::instance->scene->enemies[i]->player.death_time = 0;
		Game::instance->scene->enemies[i]->player.health = 3;
	}

}
void MenuStage::render(void)
{

	// Clear the window and the depth buffer
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();


	//set flags
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glDisable(GL_CULL_FACE);

	quad->createQuad(0, 0, 2, 2, false);
	quad2->createQuad(0, 0, 2, 2, false);
	Shader* s = Shader::Get("data/shaders/quad.vs", "data/shaders/texture.fs");
	s->enable();
	s->setUniform("u_color", Vector4(1, 1, 1, 1));
	s->setUniform("u_texture_tiling", 1.0f);
	Texture* t = Texture::Get("data/Vaporwave/menu.tga");
	Texture* t2;
	switch (selector)
	{
	case 1:
		t2 = Texture::Get("data/Vaporwave/menuPlay.tga");
		break;
	case 2:
		t2 = Texture::Get("data/Vaporwave/menuOptions.tga");
		break;
	case 3:
		t2 = Texture::Get("data/Vaporwave/menuExit.tga");
		break;

	}

	s->setTexture("u_texture", t, 0);

	quad->render(GL_TRIANGLES);
	s->setTexture("u_texture", t2, 0);

	quad2->render(GL_TRIANGLES);

}

void PauseStage::render(void)
{

	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();


	//set flags
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glDisable(GL_CULL_FACE);

	quad->createQuad(0, 0, 2, 2, false);
	quad2->createQuad(0, 0, 2, 2, false);
	Shader* s = Shader::Get("data/shaders/quad.vs", "data/shaders/texture.fs");
	s->enable();
	s->setUniform("u_color", Vector4(1, 1, 1, 1));
	s->setUniform("u_texture_tiling", 1.0f);
	Texture* t = Texture::Get("data/Vaporwave/pause.tga");
	Texture* t2;
	switch (selector)
	{
	case 1:
		t2 = Texture::Get("data/Vaporwave/pauseOptions.tga");
		break;
	case 2:
		t2 = Texture::Get("data/Vaporwave/pauseExit.tga");
		break;

	}

	s->setTexture("u_texture", t, 0);

	quad->render(GL_TRIANGLES);
	s->setTexture("u_texture", t2, 0);

	quad2->render(GL_TRIANGLES);

}

void TutorialStage::render(void)
{

	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();


	//set flags
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glDisable(GL_CULL_FACE);

	quad->createQuad(0, 0, 2, 2, false);
	quad2->createQuad(0, 0, 2, 2, false);
	Shader* s = Shader::Get("data/shaders/quad.vs", "data/shaders/texture.fs");
	s->enable();
	s->setUniform("u_color", Vector4(1, 1, 1, 1));
	s->setUniform("u_texture_tiling", 1.0f);
	Texture* t;
	Texture* t2 = Texture::Get("data/Vaporwave/continue.tga");
	switch (selector)
	{
	case 1:
		t = Texture::Get("data/Vaporwave/tutorial1.tga");
		break;
	case 2:
		t = Texture::Get("data/Vaporwave/tutorial2.tga");
		break;
	case 3:
		t = Texture::Get("data/Vaporwave/tutorial3.tga");
		break;
	case 4:
		t = Texture::Get("data/Vaporwave/tutorial4.tga");
		break;
	case 5:
		t = Texture::Get("data/Vaporwave/tutorial5.tga");
		break;
	case 6:
		t = Texture::Get("data/Vaporwave/tutorial6.tga");
		break;
	default:
		break;
	}

	s->setTexture("u_texture", t, 0);

	quad->render(GL_TRIANGLES);
	s->setTexture("u_texture", t2, 0);

	quad2->render(GL_TRIANGLES);
}

void WinLoseStage::render(void)
{

	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();


	//set flags
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glDisable(GL_CULL_FACE);

	quad->createQuad(0, 0, 2, 2, false);
	quad2->createQuad(0, 0, 2, 2, false);
	Shader* s = Shader::Get("data/shaders/quad.vs", "data/shaders/texture.fs");
	s->enable();
	s->setUniform("u_color", Vector4(1, 1, 1, 1));
	s->setUniform("u_texture_tiling", 1.0f);
	Texture* t;
	if (Game::instance->scene->myPlayer->player.health <= 0)
		t = Texture::Get("data/Vaporwave/lost.tga");
	else {
		t = Texture::Get("data/Vaporwave/win.tga");
	}
	Texture* t2;
	switch (selector)
	{
	case 1:
		t2 = Texture::Get("data/Vaporwave/pauseOptions.tga");
		break;
	case 2:
		t2 = Texture::Get("data/Vaporwave/pauseExit.tga");
		break;

	}

	s->setTexture("u_texture", t, 0);

	quad->render(GL_TRIANGLES);
	s->setTexture("u_texture", t2, 0);

	quad2->render(GL_TRIANGLES);
}

void OptionStage::render(void)
{

	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();


	//set flags
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glDisable(GL_CULL_FACE);

	quad->createQuad(0, 0, 2, 2, false);
	quad2->createQuad(0, 0, 2, 2, false);
	Shader* s = Shader::Get("data/shaders/quad.vs", "data/shaders/texture.fs");
	s->enable();
	s->setUniform("u_color", Vector4(1, 1, 1, 1));
	s->setUniform("u_texture_tiling", 1.0f);
	Texture* t = Texture::Get("data/Vaporwave/options.tga");
	Texture* t2;
	switch (selector)
	{
	case 1:
		switch (selector2)
		{
		case 0:
			t2 = Texture::Get("data/Vaporwave/0.tga");
			BASS_SetVolume(0);
			break;
		case 1:
			t2 = Texture::Get("data/Vaporwave/1.tga");
			BASS_SetVolume(0.25);
			break;
		case 2:
			t2 = Texture::Get("data/Vaporwave/2.tga");
			BASS_SetVolume(0.5);
			break;
		case 3:
			t2 = Texture::Get("data/Vaporwave/3.tga");
			BASS_SetVolume(0.75);
			break;
		case 4:
			t2 = Texture::Get("data/Vaporwave/4.tga");
			BASS_SetVolume(1);
			break;
		}
		break;
	case 2:
		t2 = Texture::Get("data/Vaporwave/optionBack.tga");
		break;

	}

	s->setTexture("u_texture", t, 0);

	quad->render(GL_TRIANGLES);
	s->setTexture("u_texture", t2, 0);

	quad2->render(GL_TRIANGLES);

}

void MenuStage::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_W)) //if key up
	{
		if (selector <= 1) {
			selector = 3;
		}
		else {
			selector -= 1;
		}


	}
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) //if key down
	{
		if (selector >= 3) {
			selector = 1;
		}
		else {
			selector += 1;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_E)) //if key A was pressed
	{
		switch (selector)
		{
		case 1:
			selector = 1;
			if (Game::instance->tutorial_done) {
				Game::instance->bass->playChannel("data/sounds/car.mp3", 0.2, true);
				changeStage("play");
			}
			else {
				changeStage("tutorial");
			}

			break;
		case 2:
			changeStage("option");
			break;
		case 3:
			exit(0);
			break;
		default:
			break;
		}


	}

	if (Input::wasKeyPressed(SDL_SCANCODE_ESCAPE)) {

		exit(0);
	}
}

void TutorialStage::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_E)) //if key up
	{
		if (selector < 6) {
			selector += 1;
		}
		else {
			Game::instance->tutorial_done = true;
			changeStage("menu");
		}
	}


}

void PauseStage::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_W)) //if key up
	{
		if (selector <= 1) {
			selector = 2;
		}
		else {
			selector -= 1;
		}


	}
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) //if key down
	{
		if (selector >= 2) {
			selector = 1;
		}
		else {
			selector += 1;
		}
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_E)) //if key A was pressed
	{
		switch (selector)
		{
		case 1:
			selector = 1;
			changeStage("option");
			Game::instance->pause_inside_game = true;
			break;
		case 2:
			changeStage("menu");
			restart();
			break;
		case 3:
			exit(0);
			break;
		default:
			break;
		}


	}

	if (Input::wasKeyPressed(SDL_SCANCODE_ESCAPE)) {

		changeStage("play");
	}
}
void WinLoseStage::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_W)) //if key up
	{
		if (selector <= 1) {
			selector = 2;
		}
		else {
			selector -= 1;
		}


	}
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) //if key down
	{
		if (selector >= 2) {
			selector = 1;
		}
		else {
			selector += 1;
		}
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_E)) //if key A was pressed
	{
		switch (selector)
		{
		case 1:
			selector = 1;
			restart();
			changeStage("play");
			break;
		case 2:
			changeStage("menu");
			restart();
			break;
		case 3:
			exit(0);
			break;
		default:
			break;
		}


	}

	if (Input::wasKeyPressed(SDL_SCANCODE_ESCAPE)) {

		changeStage("play");
	}
}

void OptionStage::update(double seconds_elapsed)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_W)) //if key up
	{
		if (selector <= 1) {
			selector = 2;
		}
		else {
			selector -= 1;
		}


	}
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) //if key down
	{
		if (selector >= 2) {
			selector = 1;
		}
		else {
			selector += 1;
		}
	}


	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key up
	{
		if (selector2 < 0) {
			selector2 = 4;
		}
		else {
			selector2 -= 1;
		}


	}
	if (Input::wasKeyPressed(SDL_SCANCODE_D)) //if key down
	{
		if (selector2 > 4) {
			selector2 = 0;
		}
		else {
			selector2 += 1;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
		if (Game::instance->pause_inside_game) {
			Game::instance->pause_inside_game = false;
			changeStage("pause");
		}
		else {
			changeStage("menu");
			restart();
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_E)) //if key A was pressed
	{
		switch (selector)
		{
		case 2:
			if (Game::instance->pause_inside_game) {
				Game::instance->pause_inside_game = false;
				changeStage("pause");
			}
			else {
				changeStage("menu");
				restart();
			}
			break;
		default:
			break;
		}


	}

	if (Input::wasKeyPressed(SDL_SCANCODE_ESCAPE)) {

		changeStage("play");
	}
}