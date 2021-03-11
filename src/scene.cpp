#include "scene.h"
#include <cmath>

Scene::Scene(int window_width, int window_height)
{
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 10.f, 10.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0

	camera->setPerspective(120.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective

	//load one texture without using the Texture Manager (Texture::Get would use the manager)

	background.push_back(new EntityMesh("data/Vaporwave/sun/sphere.obj", "data/Vaporwave/test3.tga", Vector4(1, 1, 1, 1), "fondoLila", false));
	background.push_back(new EntityMesh("data/Vaporwave/sun/sphere.obj", "data/Vaporwave/sun/sun.tga", Vector4(1, 1, 1, 1), "sun", false));
	map.push_back(new EntityMesh("data/Vaporwave/map.obj", "data/Vaporwave/gridalpha.tga", Vector4(1, 1, 1, 1), "map", false));
	vehicles.push_back(new EntityMesh("data/Vaporwave/car/source/bmw.obj", "data/Vaporwave/car/textures/NewTexture2.tga", Vector4(1, 1, 1, 1), "car", false));
	playeritems.push_back(new EntityMesh("data/Vaporwave/phone/phone.obj", "data/Vaporwave/phone/lifeselect.tga", Vector4(1, 1, 1, 1), "phone", false));
	playeritems.push_back(new EntityMesh("data/Vaporwave/arrow/arrow.obj", "data/Vaporwave/sun/sun.tga", Vector4(1, 1, 1, 1), "arrrow", false));
	//Texture a = *Texture::Get("data/Vaporwave/phone/merged3.tga");
	screenshots.push_back(Texture::Get("data/Vaporwave/phone/lifeselect.tga"));
	screenshots.push_back(Texture::Get("data/Vaporwave/phone/launderingselect.tga"));
	screenshots.push_back(Texture::Get("data/Vaporwave/phone/gunselect.tga"));
	screenshots.push_back(Texture::Get("data/Vaporwave/phone/btcselect.tga"));
	screenshots.push_back(Texture::Get("data/Vaporwave/phone/init.tga"));

	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/sun/sun.tga", Vector4(1, 1, 1, 1), "cyborg", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy1.tga", Vector4(1, 1, 1, 1), "enemy1", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy1.tga", Vector4(1, 1, 1, 1), "enemy2", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy1.tga", Vector4(1, 1, 1, 1), "enemy3", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy2.tga", Vector4(1, 1, 1, 1), "enemy4", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy2.tga", Vector4(1, 1, 1, 1), "enemy5", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy2.tga", Vector4(1, 1, 1, 1), "enemy6", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy2.tga", Vector4(1, 1, 1, 1), "enemy7", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy2.tga", Vector4(1, 1, 1, 1), "enemy8", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy9", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy10", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy11", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy12", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy13", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy14", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy15", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy3.tga", Vector4(1, 1, 1, 1), "enemy16", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy4.tga", Vector4(1, 1, 1, 1), "enemy17", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy4.tga", Vector4(1, 1, 1, 1), "enemy18", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy4.tga", Vector4(1, 1, 1, 1), "enemy19", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy4.tga", Vector4(1, 1, 1, 1), "enemy20", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy4.tga", Vector4(1, 1, 1, 1), "enemy21", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy4.tga", Vector4(1, 1, 1, 1), "enemy22", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy5.tga", Vector4(1, 1, 1, 1), "enemy23", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy5.tga", Vector4(1, 1, 1, 1), "enemy24", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy5.tga", Vector4(1, 1, 1, 1), "enemy25", true));
	players.push_back(new EntityMesh("data/Vaporwave/character/character.mesh", "data/Vaporwave/character/source/enemy5.tga", Vector4(1, 1, 1, 1), "enemy26", true));


	//plano
	map[0]->model.scale(5, 5, 5);


	//ftext = new RenderToTexture();
	//ftext->create(window_width, window_height, true);
	//shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	myCar = new Car(Vector3(0, 0, 1), 0, 0);
	myCar->ourCar.entity = vehicles[0];
	myCar->ourCar.entity->model.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	myCar->ourCar.entity->model.translate(0, 0.7, 0);
	myCar->ourCar.position = Vector3(0, 0.7, 0);
	myCar->ourCar.entity->model.scale(0.03, 0.03, 0.03);

	myPlayer = new Player(players[0], Vector3(0, 0, 0), 0, 10, playeritems[0], playeritems[1]);
	myPlayer->money.carried = 20;

	enemies.push_back(new Player(players[1], Vector3(-153, 0, 148), 50, 3, NULL, NULL));
	enemies.push_back(new Player(players[2], Vector3(-148, 0, 155), 90, 3, NULL, NULL));
	enemies.push_back(new Player(players[3], Vector3(-148, 0, 150), 45, 3, NULL, NULL));
	enemies.push_back(new Player(players[4], Vector3(-320, 0, 470), -15, 3, NULL, NULL));
	enemies.push_back(new Player(players[5], Vector3(-315, 0, 475), 90, 3, NULL, NULL));
	enemies.push_back(new Player(players[6], Vector3(-310, 0, 480), 90, 3, NULL, NULL));
	enemies.push_back(new Player(players[7], Vector3(-315, 0, 485), 90, 3, NULL, NULL));
	enemies.push_back(new Player(players[8], Vector3(-320, 0, 490), 195, 3, NULL, NULL));
	enemies.push_back(new Player(players[9], Vector3(5, 0, 390), 190, 3, NULL, NULL));
	enemies.push_back(new Player(players[10], Vector3(0, 0, 395), 145, 3, NULL, NULL));
	enemies.push_back(new Player(players[11], Vector3(10, 0, 395), 235, 3, NULL, NULL));
	enemies.push_back(new Player(players[12], Vector3(-5, 0, 400), 100, 3, NULL, NULL));
	enemies.push_back(new Player(players[13], Vector3(15, 0, 400), 280, 3, NULL, NULL));
	enemies.push_back(new Player(players[14], Vector3(0, 0, 405), 55, 3, NULL, NULL));
	enemies.push_back(new Player(players[15], Vector3(10, 0, 405), 325, 3, NULL, NULL));
	enemies.push_back(new Player(players[16], Vector3(5, 0, 410), 0, 3, NULL, NULL));
	enemies.push_back(new Player(players[17], Vector3(170, 0, 550), 30, 3, NULL, NULL));
	enemies.push_back(new Player(players[18], Vector3(165, 0, 560), 110, 3, NULL, NULL));
	enemies.push_back(new Player(players[19], Vector3(160, 0, 550), 30, 3, NULL, NULL));
	enemies.push_back(new Player(players[20], Vector3(155, 0, 560), 90, 3, NULL, NULL));
	enemies.push_back(new Player(players[21], Vector3(170, 0, 570), 110, 3, NULL, NULL));
	enemies.push_back(new Player(players[22], Vector3(160, 0, 570), 110, 3, NULL, NULL));
	enemies.push_back(new Player(players[23], Vector3(-410, 0, 0), 0, 3, NULL, NULL));
	enemies.push_back(new Player(players[24], Vector3(-400, 0, 0), 0, 3, NULL, NULL));
	enemies.push_back(new Player(players[25], Vector3(-390, 0, 0), 0, 3, NULL, NULL));
	enemies.push_back(new Player(players[26], Vector3(-380, 0, 0), 0, 3, NULL, NULL));



	//sol
	background[0]->model.setTranslation((myPlayer->player.entity->model * Vector3(0, 12, 0)).x, (myPlayer->player.entity->model * Vector3(0, 12, 0)).y, (myPlayer->player.entity->model * Vector3(0, 12, 0)).z);
	background[0]->model.scale(1000, 1000, 1000);
	background[1]->model.setTranslation((myPlayer->player.entity->model * Vector3(0, 12, 0)).x - 900, (myPlayer->player.entity->model * Vector3(0, 12, 0)).y, (myPlayer->player.entity->model * Vector3(0, 12, 0)).z);
	background[1]->model.scale(200, 200, 200);

	for (int i = 0; i < players.size(); i++) {
		players[i]->animations.push_back(Animation::Get("data/Vaporwave/character/animations_idle.skanim"));
		players[i]->animations.push_back(Animation::Get("data/Vaporwave/character/animations_walking.skanim"));
		players[i]->animations.push_back(Animation::Get("data/Vaporwave/character/animations_walking_backward.skanim"));
		players[i]->animations.push_back(Animation::Get("data/Vaporwave/character/animations_running.skanim"));
		players[i]->animations.push_back(Animation::Get("data/Vaporwave/character/animations_cross_punch.skanim"));
		players[i]->animations.push_back(Animation::Get("data/Vaporwave/character/animations_falling_back_death.skanim"));
		players[i]->animations.push_back(Animation::Get("data/Vaporwave/character/animations_gathering_objects.skanim"));
	}

}


void Scene::render(void)
{

	Vector3 eye;
	Vector3 center;
	if (freecamera == false) {
		if (car) {
			eye = myCar->ourCar.entity->model * Vector3(0, 60, -180);
			center = myCar->ourCar.entity->model * Vector3();
			camera->lookAt(eye, center, Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
			camera->rotate(myCar->ourCar.steer_input * 40 * DEG2RAD, Vector3(0, 1, 0));
			camera->rotate(myCar->ourCar.steer_input * 40 * DEG2RAD, Vector3(0, 0, 1));

		}
		else {
			eye = myPlayer->player.entity->model * Vector3(0, 15, -12);
			center = myPlayer->player.entity->model * Vector3(0, 12, 0);
			camera->lookAt(eye, center, Vector3(0.f, 1.f, 0.f));

		}
	}
	background[1]->model.setTranslation(center.x - 900, center.y, center.z);

	background[0]->model.setTranslation(center.x, center.y, center.z);

	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();

	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);


	//upload uniforms
	for (int i = 0; i < background.size(); i++)
		background[i]->render();

	for (int i = 0; i < map.size(); i++)
		map[i]->render();

	for (int i = 0; i < vehicles.size(); i++)
		vehicles[i]->render();

	if (phoneout) {
		playeritems[0]->render();
	}

	if (!car) {
		players[0]->render();
		playeritems[1]->render();
	}

	for (int i = 1; i < players.size(); i++)
		players[i]->render();

	myPlayer->renderHealthBar();
	myPlayer->renderMoney();

	glDisable(GL_DEPTH_TEST);

}

void Scene::update(double seconds_elapsed)
{
	float sp = 1;

	if (myPlayer->money.carried >= 20000 || myPlayer->player.health <= 0) {
		Stage::changeStage("winlose");
	}

	if (!freecamera) {
		for (int i = 0; i < enemies.size(); i++)
			enemies[i]->updateEnemy(seconds_elapsed, myPlayer);

		if (car) {
			myCar->updateCar(seconds_elapsed);
		}
		else {
			myPlayer->updatePlayer(seconds_elapsed);
			myPlayer->updateArrow();
		}


		myPlayer->updatePhone();

	}

	if (Input::wasKeyPressed(SDL_SCANCODE_1)) {

		freecamera = !freecamera;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) {

		sp = 30;
	}
	if (freecamera) {
		if (Input::isKeyPressed(SDL_SCANCODE_W)) camera->move(Vector3(0.0f, 0.0f, 1.0f) * 20 * seconds_elapsed * sp);
		if (Input::isKeyPressed(SDL_SCANCODE_S)) camera->move(Vector3(0.0f, 0.0f, -1.0f) * 20 * seconds_elapsed * sp);
		if (Input::isKeyPressed(SDL_SCANCODE_A)) camera->move(Vector3(1.0f, 0.0f, 0.0f) * 20 * seconds_elapsed * sp);
		if (Input::isKeyPressed(SDL_SCANCODE_D)) camera->move(Vector3(-1.0f, 0.0f, 0.0f) * 20 * seconds_elapsed * sp);
		camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
		camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
	}

}

