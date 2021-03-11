#ifndef PHONE //macros to ensure the code is included once
#define PHONE

#include "utils.h"
#include "entity.h"

class Phone
{
public:

	EntityMesh* entity;

	Phone();
	void Phone::updatePhone(Player* myPlayer);
};

#endif