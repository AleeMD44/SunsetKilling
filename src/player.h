#ifndef PLAYER //macros to ensure the code is included once
#define PLAYER

#include "utils.h"
#include "entity.h"

enum { IDLE, CHASING, FIGHT, LOST, DEAD };

struct myPlayer
{
	Vector3 initPos;
	Vector3 position;
	float angle;
	float acceleration_input;
	EntityMesh* entity;
	int state;
	int health;
	bool running;
	float death_time;
	bool healthmod;

	myPlayer() { acceleration_input = 0; angle = 0.0; state = IDLE; health = 10; running = false; death_time = 0; healthmod = false; }

};

struct myPhone
{
	EntityMesh* entity;
	int selector;
	int moneypersecond;

	myPhone() { selector = 0; moneypersecond = 0; }
};
struct myArrow
{
	EntityMesh* entity;
	int targetEnemy;
	myArrow() { targetEnemy = -1; }
};
struct myPunch
{
	EntityMesh* entity;
	float timeleft;
	bool hit;
	myPunch() { timeleft = 0; hit = false; }
};

struct myMoney
{
	float timeleft;
	int carried;
	bool looted;
	bool pmoneymod;

	myMoney() { timeleft = 0; carried = (rand() % 80) + 10; looted = false; pmoneymod = false; }
};

class Player
{
public:
	myPhone phone;
	myPlayer player;
	myPunch punch;
	myArrow arrow;
	myMoney money;



	//Animation* anim;
	Player(EntityMesh* plr, Vector3 pos, int angle, int heal, EntityMesh* ph, EntityMesh* arr);
	void Player::loadPhone(EntityMesh* pn);
	void Player::updatePhone();
	void Player::directArrow(Player* target);
	void Player::updateArrow();
	void Player::changePhoneScreen(int selector);
	void Player::updateEnemy(double seconds_elapsed, Player* target);
	void Player::updatePlayer(double seconds_elapsed);
	bool Player::testcolisions(Vector3 target_pos);
	void Player::renderHealthBar();
	void Player::renderMoney();
	bool Player::checkIfEnemyFront(Player* target);
	void Player::playHit();
};

#endif