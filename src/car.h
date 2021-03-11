#ifndef CAR //macros to ensure the code is included once
#define CAR

#include "utils.h"
#include "entity.h"

struct myCar
{
	Vector3 front_vector;
	Vector3 position;
	EntityMesh* entity;
	float acceleration_input;
	float steer_input;

};

class Car
{
public:

	myCar ourCar;

	Car(Vector3 f, float a, float b);

	void Car::updateCar(double seconds_elapsed);
	bool Car::testcolisions(Vector3 target_pos);
};

#endif