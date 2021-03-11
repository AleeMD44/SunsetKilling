#include "phone.h"
#include "player.cpp"
Phone::Phone(){
}

void Phone::updatePhone(Player* myPlayer) {
	*(entity->model) = myPlayer->player.l;

	entity->model->rotate(190 * DEG2RAD, Vector3(0, 1, 0));
	entity->model->rotate(15 * DEG2RAD, Vector3(1, 0, 0));
	//l.rotate(15 * DEG2RAD, Vector3(0, 0, 0));

	entity->model->translate(13, -3, 14);
	entity->model->scale(4, 4, 4);
}
