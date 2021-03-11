#include "player.h"
#include "input.h"
#include "game.h"

Player::Player(EntityMesh* plr, Vector3 pos, int angle, int heal, EntityMesh* ph, EntityMesh* arr) {
	player.entity = plr;
	phone.entity = ph;
	arrow.entity = arr;
	player.entity->model.rotate(angle * DEG2RAD, Vector3(0, 1, 0));
	player.angle = (angle + 90) * DEG2RAD;
	player.position = pos;
	player.initPos = pos;
	player.health = heal;
	player.entity->model.scale(0.15, 0.15, 0.15);
}

void Player::loadPhone(EntityMesh* pn) {
	phone.entity = pn;
}

void Player::updatePhone() {

	if (Game::instance->scene->phoneout) {
		if (Input::mouse_wheel_delta == 1) {
			if (phone.selector < 3) {
				phone.selector += 1;
			}
			else {
				phone.selector = 0;
			}
			Game::instance->bass->playChannel("data/sounds/phonein.mp3", 0.2, false);
			Input::mouse_wheel_delta = 0;
			changePhoneScreen(phone.selector);
		}
		else if (Input::mouse_wheel_delta == -1) {
			if (phone.selector > 0) {
				phone.selector -= 1;
			}
			else {
				phone.selector = 3;
			}
			Game::instance->bass->playChannel("data/sounds/phonein.mp3", 0.2, false);
			Input::mouse_wheel_delta = 0;
			changePhoneScreen(phone.selector);
		}

		if (Input::wasKeyPressed(SDL_SCANCODE_E) && Game::instance->scene->phoneout) {

			switch (phone.selector)
			{
			case 0:
				if (money.carried >= 10 && player.health < 10) {
					player.health += 1;
					money.carried -= 10;
					Game::instance->bass->playChannel("data/sounds/money.mp3", 0.2, false);
				}
				break;
			case 1:
				if (money.carried >= 200) {
					phone.moneypersecond += 5;
					money.carried -= 200;
					Game::instance->bass->playChannel("data/sounds/money.mp3", 0.2, false);
				}
				break;
			case 2:
				if (money.carried >= 400) {
					phone.moneypersecond += 15;
					money.carried -= 400;
					Game::instance->bass->playChannel("data/sounds/money.mp3", 0.2, false);
				}
				break;
			case 3:
				if (money.carried >= 900) {
					phone.moneypersecond += 35;
					money.carried -= 900;
					Game::instance->bass->playChannel("data/sounds/money.mp3", 0.2, false);
				}
				break;
			default:
				break;
			}

		}

		if (!Game::instance->scene->car) {
			phone.entity->model = player.entity->model;

			phone.entity->model.rotate(190 * DEG2RAD, Vector3(0, 1, 0));
			phone.entity->model.rotate(15 * DEG2RAD, Vector3(1, 0, 0));

			phone.entity->model.translate(13, -3, 14);
			phone.entity->model.scale(4, 4, 4);

		}

		else {
			phone.entity->model = Game::instance->scene->vehicles[0]->model;
			phone.entity->model.rotate(190 * DEG2RAD, Vector3(0, 1, 0));
			phone.entity->model.rotate(15 * DEG2RAD, Vector3(1, 0, 0));

			phone.entity->model.translate(70, -30, 180);
			phone.entity->model.scale(12, 12, 12);
		}

	}

	if (fmod(Game::instance->time, 5) <= 0.01 && !money.pmoneymod) {
		money.carried += phone.moneypersecond;
		money.pmoneymod = true;
	}
	else if (fmod(Game::instance->time, 5) >= 3) {
		money.pmoneymod = false;
	}
}

void Player::changePhoneScreen(int selector) {
	phone.entity->texture = Game::instance->scene->screenshots[selector];
}

void Player::directArrow(Player* target) {
	Vector3 front_vector = player.entity->model.frontVector();
	Vector3 toTarget = Vector3(target->player.position.x - player.position.x, target->player.position.y - player.position.y, target->player.position.z - player.position.z);

	float angle = dot(front_vector, toTarget);

	float distance = sqrt(pow(toTarget.x, 2) + pow(toTarget.z, 2));

	float fangle = atan2(toTarget.x * front_vector.z - front_vector.x * toTarget.z, toTarget.x * toTarget.z + front_vector.x * front_vector.z);

	float angled2 = acos(angle / (distance * sqrt(pow(front_vector.x, 2) + pow(front_vector.z, 2))));

	if (fangle < 0)
		angled2 *= -1;

	arrow.entity->model = player.entity->model;
	arrow.entity->model.rotate(-80 * DEG2RAD, Vector3(1, 0, 0));
	arrow.entity->model.rotate(angled2, Vector3(0, 0, 1));
	arrow.entity->model.scale(10, 10, 10);
	arrow.entity->model.translate(0, 0, -2.2);

}
void Player::updateArrow() {
	if (arrow.targetEnemy != -1) {
		directArrow(Game::instance->scene->enemies[arrow.targetEnemy]);
		if (Game::instance->scene->enemies[arrow.targetEnemy]->player.entity->noColision) {
			arrow.targetEnemy = -1;
			std::rotate(Game::instance->scene->enemies.begin(),
				Game::instance->scene->enemies.end() - 1, // this will be the new first element
				Game::instance->scene->enemies.end());
		}

	}
	else {
		for (int i = Game::instance->scene->enemies.size() - 1; i >= 0; i--) {
			if (!Game::instance->scene->enemies[i]->player.entity->noColision) {
				arrow.targetEnemy = i;
			}
		}
		if (arrow.targetEnemy == -1) {
			directArrow(Game::instance->scene->enemies[0]);
		}
	}

}

void Player::updateEnemy(double seconds_elapsed, Player* target) {
	Vector3 front_vector = player.entity->model.frontVector();
	Vector3 toTarget = Vector3(target->player.position.x - player.position.x, target->player.position.y - player.position.y, target->player.position.z - player.position.z);

	float angle = dot(front_vector, toTarget);

	float distance = sqrt(pow(toTarget.x, 2) + pow(toTarget.z, 2));

	float angled = atan2(toTarget.z, toTarget.x);

	float fangle = atan2(toTarget.x * front_vector.z - front_vector.x * toTarget.z, toTarget.x * toTarget.z + front_vector.x * front_vector.z);

	float angled2 = acos(angle / (distance * sqrt(pow(front_vector.x, 2) + pow(front_vector.z, 2))));

	if (fangle < 0)
		angled2 *= -1;

	for (int i = 0; i < player.entity->animations.size() - 2; i++) {
		player.entity->animations[i]->assignTime(Game::instance->time);

	}

	switch (player.state)
	{
	case IDLE:
		player.entity->noColision = false;

		if (player.health == 0) {
			punch.timeleft = player.entity->animations[5]->duration;
			player.state = DEAD;
			player.death_time = Game::instance->time;
			player.entity->noColision = true;
		}
		if (abs(angled2) < 0.5 && distance < 10 && distance > 1) {

			player.state = CHASING;
		}
		if (player.acceleration_input > 0)
			player.acceleration_input -= 2.55 * seconds_elapsed;
		if (player.acceleration_input < 0)
			player.acceleration_input = 0;

		if (player.acceleration_input >= 0)
			blendSkeleton(&(player.entity->animations[0]->skeleton), &(player.entity->animations[1]->skeleton), player.acceleration_input * 0.5, player.entity->skeleton);

		break;
	case CHASING:

		if (player.health == 0) {
			punch.timeleft = player.entity->animations[5]->duration;
			player.state = DEAD;
			player.death_time = Game::instance->time;
			player.entity->noColision = true;
		}

		if (distance < 10 && distance > 1) {
			Vector3 target_pos = player.position;

			player.acceleration_input += 4 * seconds_elapsed;

			player.entity->model.rotate(angled - player.angle, Vector3(0, 1, 0));

			player.angle = angled;

			target_pos = target_pos + (front_vector * player.acceleration_input * 4 * seconds_elapsed);

			if (!testcolisions(target_pos)) { player.position = target_pos; }

			if (player.acceleration_input > 0)
				player.acceleration_input -= 0.55 * seconds_elapsed;
			else if (player.acceleration_input < 0) {
				player.acceleration_input += 0.55 * seconds_elapsed;
			}
			if (player.acceleration_input > 4) {
				player.acceleration_input = 4;
			}
			if (player.acceleration_input >= 0)
				blendSkeleton(&(player.entity->animations[0]->skeleton), &(player.entity->animations[1]->skeleton), player.acceleration_input * 0.5, player.entity->skeleton);

		}
		else if (distance < 1 && !Game::instance->scene->car) {

			player.acceleration_input = 0;
			player.state = FIGHT;
		}
		else {
			player.state = LOST;
		}


		break;
	case FIGHT:
		player.entity->noColision = false;

		player.entity->model.rotate(angled - player.angle, Vector3(0, 1, 0));

		player.angle = angled;

		if (player.health == 0) {
			punch.timeleft = player.entity->animations[5]->duration;
			player.state = DEAD;
			player.death_time = Game::instance->time;
			player.entity->noColision = true;
		}

		if (!punch.hit && distance < 1.1 && punch.timeleft > player.entity->animations[4]->duration / 2 - seconds_elapsed && punch.timeleft < player.entity->animations[4]->duration / 2 && Game::instance->scene->myPlayer->player.health > 0) {
			Game::instance->scene->myPlayer->player.health -= 1;
			punch.hit = true;
			playHit();
		}
		if (punch.timeleft > 0) {
			player.entity->animations[4]->assignTime(-punch.timeleft + player.entity->animations[4]->duration);//t * player.entity->animations[3]->duration);
			blendSkeleton(player.entity->skeleton, &(player.entity->animations[4]->skeleton), sin(punch.timeleft), player.entity->skeleton);
			punch.timeleft -= seconds_elapsed;
		}
		else {
			punch.timeleft = player.entity->animations[4]->duration;
			punch.hit = false;
		}
		if (Game::instance->scene->car) {
			punch.timeleft = 0;
			punch.hit = false;
			player.state = LOST;
		}
		if (distance > 1.1) {
			punch.timeleft = 0;
			punch.hit = false;
			player.state = CHASING;
		}
		break;
	case DEAD:
		if (punch.timeleft > 0.1) {
			if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/dead.mp3")) != BASS_ACTIVE_PLAYING)
				Game::instance->bass->playChannel("data/sounds/dead.mp3", 0.1, false);
			player.entity->animations[5]->assignTime(-punch.timeleft + player.entity->animations[5]->duration);
			blendSkeleton(player.entity->skeleton, &(player.entity->animations[5]->skeleton), 1, player.entity->skeleton);
			punch.timeleft -= seconds_elapsed;
		}

		if (fmod(Game::instance->time - player.death_time + 0.01, 380) <= 0.01) {

			player.state = LOST;
			money.carried = (rand() % 80) + 10;
			money.looted = false;
			player.death_time = 0;
			player.health = 3;

		}
		break;
	case LOST:
		Vector3 toTargetPos = Vector3(player.initPos.x - player.position.x, player.initPos.y - player.position.y, player.initPos.z - player.position.z);

		float angle1 = dot(front_vector, toTargetPos);

		float distance1 = sqrt(pow(toTargetPos.x, 2) + pow(toTargetPos.z, 2));

		float angled1 = atan2(toTargetPos.z, toTargetPos.x);


		if (distance1 > 0.5) {
			player.acceleration_input += 4 * seconds_elapsed;

			float finalAngle1 = angled1 - player.angle;

			Vector3 target_pos = player.position;

			player.angle = angled1;

			target_pos = target_pos + (front_vector * player.acceleration_input * 4 * seconds_elapsed);

			if (!testcolisions(target_pos)) { player.position = target_pos; }

			player.entity->model.rotate(finalAngle1, Vector3(0, 1, 0));

			if (player.acceleration_input > 0)
				player.acceleration_input -= 0.55 * seconds_elapsed;
			else if (player.acceleration_input < 0) {
				player.acceleration_input += 0.55 * seconds_elapsed;
			}
			if (player.acceleration_input > 4) {
				player.acceleration_input = 4;
			}
			if (player.acceleration_input >= 0)
				blendSkeleton(&(player.entity->animations[0]->skeleton), &(player.entity->animations[1]->skeleton), player.acceleration_input * 0.5, player.entity->skeleton);
		}
		else	if (player.health == 0) {
			punch.timeleft = player.entity->animations[5]->duration;
			player.entity->noColision = true;
			player.death_time = Game::instance->time;
			player.state = DEAD;
		}
		else {
			player.acceleration_input = 0;
			player.state = IDLE;
		}

		break;


	}



	//comprobamos si colisiona el objeto con la esfera (radio 3)
	player.entity->model.setTranslation(player.position.x, player.position.y, player.position.z);


}

void Player::updatePlayer(double seconds_elapsed) {

	for (int i = 0; i < player.entity->animations.size() - 2; i++) {
		player.entity->animations[i]->assignTime(Game::instance->time);
	}

	Vector3 front_vector = player.entity->model.frontVector().normalize();
	Vector3 right_vector = player.entity->model.rightVector().normalize();
	Vector3 target_pos = player.position;

	if (Input::isKeyPressed(SDL_SCANCODE_W)) {
		if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/walking.mp3")) != BASS_ACTIVE_PLAYING)
			Game::instance->bass->playChannel("data/sounds/walking.mp3", 0.4, true);
		player.acceleration_input += 1.2 * seconds_elapsed;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S)) {
		player.acceleration_input -= 1.2 * seconds_elapsed;
	};
	if (abs(player.acceleration_input) < 0.3) {
		if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/walking.mp3")) == BASS_ACTIVE_PLAYING)
			Game::instance->bass->stopChannel("data/sounds/walking.mp3");
	}
	target_pos = target_pos + (front_vector * player.acceleration_input * 4 * seconds_elapsed);
	if (!Input::isKeyPressed(SDL_SCANCODE_LSHIFT) && !player.running) {
		if (player.acceleration_input > 1)
			player.acceleration_input = 1;
	}
	else if (player.running && player.acceleration_input < 1) {
		player.running = false;
		if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/running.mp3")) == BASS_ACTIVE_PLAYING)
			Game::instance->bass->stopChannel("data/sounds/running.mp3");
		if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/walking.mp3")) != BASS_ACTIVE_PLAYING)
			Game::instance->bass->playChannel("data/sounds/walking.mp3", 0.4, true);
	}
	else {
		if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/walking.mp3")) == BASS_ACTIVE_PLAYING)
			Game::instance->bass->stopChannel("data/sounds/walking.mp3");
		if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/running.mp3")) != BASS_ACTIVE_PLAYING)
			Game::instance->bass->playChannel("data/sounds/running.mp3", 0.4, true);
		player.running = true;
		if (player.acceleration_input > 2)
			player.acceleration_input = 2;
	}

	if (player.acceleration_input < -1)
		player.acceleration_input = -1;

	if (player.acceleration_input > 0)
		player.acceleration_input -= 0.55 * seconds_elapsed;

	else if (player.acceleration_input < 0) {
		player.acceleration_input += 0.55 * seconds_elapsed;
	}

	if (player.acceleration_input >= 0 && player.acceleration_input <= 1)
		blendSkeleton(&(player.entity->animations[0]->skeleton), &(player.entity->animations[1]->skeleton), player.acceleration_input * 2, player.entity->skeleton);
	else
		blendSkeleton(&(player.entity->animations[1]->skeleton), &(player.entity->animations[3]->skeleton), player.acceleration_input - 1, player.entity->skeleton);

	if (player.acceleration_input < 0)
		blendSkeleton(&(player.entity->animations[0]->skeleton), &(player.entity->animations[2]->skeleton), player.acceleration_input * -2, player.entity->skeleton);

	if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
		punch.timeleft = player.entity->animations[4]->duration;
		punch.hit = false;
	};

	if (punch.timeleft > 0) {
		player.acceleration_input = 0;
		player.entity->animations[4]->assignTime(-punch.timeleft + player.entity->animations[4]->duration);//t * player.entity->animations[3]->duration);
		blendSkeleton(player.entity->skeleton, &(player.entity->animations[4]->skeleton), sin(punch.timeleft), player.entity->skeleton);//, UPPER_BODY);
		punch.timeleft -= seconds_elapsed;
	}

	if (!punch.hit && punch.timeleft > player.entity->animations[4]->duration / 2 - seconds_elapsed && punch.timeleft < player.entity->animations[4]->duration / 2)
		for (int i = 0; i < Game::instance->scene->enemies.size(); i++) {
			if (Game::instance->scene->enemies[i]->player.health > 0) {
				if (checkIfEnemyFront(Game::instance->scene->enemies[i])) {
					Game::instance->scene->enemies[i]->player.health -= 1;
					Game::instance->scene->enemies[i]->player.state = CHASING;
					punch.hit = true;
					playHit();
				}
				if (Game::instance->scene->enemies[i]->player.position.distance(player.position) < 10) {
					Game::instance->scene->enemies[i]->player.state = CHASING;
				}
			}
		}
	if (!testcolisions(target_pos)) {
		player.position = target_pos;
	}
	else {
		blendSkeleton(&(player.entity->animations[0]->skeleton), &(player.entity->animations[1]->skeleton), 0, player.entity->skeleton);
		player.acceleration_input = 0;
	}

	player.angle = Input::mouse_delta.x * seconds_elapsed * -100;
	player.entity->model.setTranslation(player.position.x, player.position.y, player.position.z);
	player.entity->model.rotate(player.angle * DEG2RAD, Vector3(0, 1, 0));

	if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
		Vector3 toTarget = Game::instance->scene->myCar->ourCar.position - player.position;
		float distance = sqrt(pow(toTarget.x, 2) + pow(toTarget.z, 2));
		if (distance < 1.5) {
			Game::instance->scene->myCar->ourCar.acceleration_input = 0;
			Game::instance->scene->car = true;
			player.acceleration_input = 0;
			Game::instance->bass->playChannel("data/sounds/car.mp3", 0.2, true);
			if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/walking.mp3")) == BASS_ACTIVE_PLAYING)
				Game::instance->bass->stopChannel("data/sounds/walking.mp3");
		}
		else {
			for (int i = 0; i < Game::instance->scene->enemies.size(); i++) {
				if (checkIfEnemyFront(Game::instance->scene->enemies[i]) && !Game::instance->scene->enemies[i]->money.looted && Game::instance->scene->enemies[i]->player.entity->noColision) {
					money.carried += Game::instance->scene->enemies[i]->money.carried;
					Game::instance->scene->enemies[i]->money.carried = 0;
					Game::instance->scene->enemies[i]->money.looted = true;
					money.timeleft = player.entity->animations[6]->duration;
					if (BASS_ChannelIsActive(*Game::instance->bass->getChannel("data/sounds/gather.mp3")) != BASS_ACTIVE_PLAYING)
						Game::instance->bass->playChannel("data/sounds/gather.mp3", 0.2, false);
				}
			}
		}
	}
	if (money.timeleft > 0) {
		player.acceleration_input = 0;
		player.entity->animations[6]->assignTime(-money.timeleft + player.entity->animations[6]->duration);
		blendSkeleton(player.entity->skeleton, &(player.entity->animations[6]->skeleton), 1, player.entity->skeleton);
		Camera::current->fov = 120 - 10 * sin((1.66 * money.timeleft) / PI);
		money.timeleft -= seconds_elapsed;
		if (money.timeleft <= 0)
			Camera::current->fov = 120;
	}

	if (fmod(Game::instance->time, 20) <= 0.01 && !player.healthmod) {
		if (player.health < 10)
			player.health += 1;
		player.healthmod = true;
	}
	else if (fmod(Game::instance->time, 20) >= 5) {
		player.healthmod = false;
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_TAB)) {

		Game::instance->scene->phoneout = !Game::instance->scene->phoneout;
		if (Game::instance->scene->phoneout)
			Game::instance->bass->playChannel("data/sounds/phonein.mp3", 0.2, false);
		else
			Game::instance->bass->playChannel("data/sounds/phoneout.mp3", 0.2, false);
	}
}

bool Player::testcolisions(Vector3 target_pos) {

	Vector3 character_center = target_pos + Vector3(0, 3.2, 0);
	Vector3 character_center1 = target_pos + Vector3(0, 0.5, 0);
	//para cada objecto de la escena...
	Vector3 coll;
	Vector3 collnorm;
	if (Game::instance->scene->map[0]->mesh->testSphereCollision(Game::instance->scene->map[0]->model, character_center, 0.6, coll, collnorm)) {
		return true;
		//	printf("he chocao \n");
	}

	if (Game::instance->scene->vehicles[0]->mesh->testSphereCollision(Game::instance->scene->vehicles[0]->model, character_center1, 3, coll, collnorm)) {
		return true;
	}

	for (int i = 0; i < Game::instance->scene->players.size(); i++) {
		if (Game::instance->scene->players[i]->name != player.entity->name && !Game::instance->scene->players[i]->noColision)
			if (Game::instance->scene->players[i]->mesh->testSphereCollision(Game::instance->scene->players[i]->model, character_center1, 3, coll, collnorm))
				return true;
	}
	return false;
}

bool Player::checkIfEnemyFront(Player* target) {
	Vector3 front_vector = player.entity->model.frontVector();
	Vector3 toTarget = Vector3(target->player.position.x - player.position.x, target->player.position.y - player.position.y, target->player.position.z - player.position.z);

	float angle = dot(front_vector, toTarget);

	float distance = sqrt(pow(toTarget.x, 2) + pow(toTarget.z, 2));

	float fangle = atan2(toTarget.x * front_vector.z - front_vector.x * toTarget.z, toTarget.x * toTarget.z + front_vector.x * front_vector.z);

	float angled2 = acos(angle / (distance * sqrt(pow(front_vector.x, 2) + pow(front_vector.z, 2))));

	if (fangle < 0)
		angled2 *= -1;

	if (abs(angled2) < 0.3 && distance <= 1.1) {
		return true;
	}

	return false;
}
void Player::renderMoney() {
	std::string s = std::to_string(money.carried);

	s = s.append("$");

	float res;

	for (int i = 0; i < s.size(); i++) {

		res = cos(i + 1 * Game::instance->time);
		if (res < 0)
			res *= -1;
		drawText(Game::instance->window_width / 2 - 30 + i * 15, Game::instance->window_height - 80, std::string(1, s.at(i)), Vector3(1, res, 1), 3);
	}

}
void Player::renderHealthBar() {
	float res = cos((5 - player.health) * Game::instance->time);
	if (res < 0)
		res *= -1;
	Vector3 v = Vector3(1, res, res);

	switch (player.health)
	{
	case 0:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|          |", v, 3);
		break;
	case 1:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|-         |", v, 3);
		break;
	case 2:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|--        |", v, 3);
		break;
	case 3:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|---       |", v, 3);
		break;
	case 4:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|----      |", v, 3);
		break;
	case 5:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|-----     |", Vector3(1, 1, 1), 3);
		break;
	case 6:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|------    |", Vector3(1, 1, 1), 3);
		break;
	case 7:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|-------   |", Vector3(1, 1, 1), 3);
		break;
	case 8:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|--------  |", Vector3(1, 1, 1), 3);
		break;
	case 9:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|--------- |", Vector3(1, 1, 1), 3);
		break;
	case 10:
		drawText(Game::instance->window_width / 2 - 100, Game::instance->window_height - 50, "|----------|", Vector3(1, 1, 1), 3);
		break;

	}
}

void Player::playHit() {

	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i < 5; ++i) myvector.push_back(i);

	// using built-in random generator:
	std::random_shuffle(myvector.begin(), myvector.end());
	std::string a = "data/sounds/hit";
	a.append(std::to_string(myvector[0]));
	a.append(".mp3");
	std::string b = "data/sounds/hit";
	b.append(std::to_string(myvector[1]));
	b.append(".mp3");
	std::string c = "data/sounds/hit";
	c.append(std::to_string(myvector[2]));
	c.append(".mp3");
	std::string d = "data/sounds/hit";
	d.append(std::to_string(myvector[3]));
	d.append(".mp3");
	if (BASS_ChannelIsActive(*Game::instance->bass->getChannel(a.c_str())) != BASS_ACTIVE_PLAYING) {
		Game::instance->bass->playChannel(a.c_str(), 0.2, false);
	}
	else if (BASS_ChannelIsActive(*Game::instance->bass->getChannel(b.c_str())) != BASS_ACTIVE_PLAYING) {
		Game::instance->bass->playChannel(b.c_str(), 0.2, false);
	}
	else if (BASS_ChannelIsActive(*Game::instance->bass->getChannel(c.c_str())) != BASS_ACTIVE_PLAYING) {
		Game::instance->bass->playChannel(c.c_str(), 0.2, false);
	}
	else if (BASS_ChannelIsActive(*Game::instance->bass->getChannel(d.c_str())) != BASS_ACTIVE_PLAYING) {
		Game::instance->bass->playChannel(d.c_str(), 0.2, false);
	}

}