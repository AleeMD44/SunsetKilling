#include "car.h"
#include "input.h"
#include "game.h"

Car::Car(Vector3 f, float a, float b) {
	ourCar.front_vector = f;
	ourCar.acceleration_input = a;
	ourCar.steer_input = b;
}

void Car::updateCar(double seconds_elapsed)
{

	ourCar.front_vector = ourCar.entity->model.frontVector().normalize();
	Vector3 acceleration_vector = ourCar.front_vector * ourCar.acceleration_input * 1800 * seconds_elapsed;
	Vector3 target_pos = ourCar.position;

	if (abs(acceleration_vector.x) > 0.001 || abs(acceleration_vector.z) > 0.001) {

		if (Input::isKeyPressed(SDL_SCANCODE_A)) {
			if (ourCar.acceleration_input > 0) ourCar.steer_input -= seconds_elapsed * 0.3;
			else ourCar.steer_input += seconds_elapsed * 0.3;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_D)) {
			if (ourCar.acceleration_input > 0) ourCar.steer_input += seconds_elapsed * 0.3;
			else ourCar.steer_input -= seconds_elapsed * 0.3;
		}

		if (ourCar.steer_input > 0.1) ourCar.steer_input = 0.1;
		if (ourCar.steer_input < -0.1) ourCar.steer_input = -0.1;

		ourCar.entity->model.rotate(ourCar.steer_input * seconds_elapsed * 500 * DEG2RAD, Vector3(0, 1, 0));
	}


	if (Input::isKeyPressed(SDL_SCANCODE_W)) {
		ourCar.acceleration_input += 0.015 * seconds_elapsed;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_S)) {
		ourCar.acceleration_input -= 0.015 * seconds_elapsed;
	}

	target_pos = ourCar.position + acceleration_vector;

	if (!testcolisions(target_pos)) { ourCar.position = target_pos; }
	else {
		acceleration_vector = acceleration_vector * -0.2;
		ourCar.acceleration_input = ourCar.acceleration_input * -0.2;
	};

	ourCar.entity->model.setTranslation(ourCar.position.x, ourCar.position.y, ourCar.position.z);

	if (ourCar.steer_input > 0)
		ourCar.steer_input -= 0.22 * seconds_elapsed;
	else if (ourCar.steer_input < 0) {
		ourCar.steer_input += 0.22 * seconds_elapsed;
	}

	if (ourCar.acceleration_input > 0)
		ourCar.acceleration_input -= 0.01 * seconds_elapsed;
	else if (ourCar.acceleration_input < 0) {
		ourCar.acceleration_input += 0.01 * seconds_elapsed;
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_E)) {

		if (abs(ourCar.acceleration_input) < 0.005) {
			Vector3 eye = Game::instance->scene->myPlayer->player.entity->model * Vector3(0, 15, -12);
			Vector3 center = Game::instance->scene->myPlayer->player.entity->model * Vector3(0, 12, 0);
			Game::instance->scene->camera->lookAt(eye, center, Vector3(0.f, 1.f, 0.f));
			Game::instance->scene->myPlayer->player.position.x = ourCar.position.x;
			Game::instance->scene->myPlayer->player.position.z = ourCar.position.z;
			Game::instance->scene->myPlayer->player.position = Game::instance->scene->myPlayer->player.position + ourCar.front_vector * Vector3(-1, 0, -1);
			Game::instance->scene->myPlayer->player.position = Game::instance->scene->myPlayer->player.position + ourCar.entity->model.rightVector().normalize() * Vector3(-1.5, 0, -1.5);
			Game::instance->scene->car = false;
			Game::instance->bass->stopChannel("data/sounds/car.mp3");
		}
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_TAB)) {

		Game::instance->scene->phoneout = !Game::instance->scene->phoneout;
	}

}

bool Car::testcolisions(Vector3 target_pos) {

	Vector3 character_center = target_pos + Vector3(0, 2, 0);
	Vector3 coll;
	Vector3 collnorm;
	if (Game::instance->scene->map[0]->mesh->testSphereCollision(Game::instance->scene->map[0]->model, character_center, 0.5, coll, collnorm) == true) {
		return true;
	}

	return false;
}