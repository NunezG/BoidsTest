

#ifndef BOID_H
#define BOID_H

#include "../GameObject.h"

class CBoid {

public:

	point2F position;
	point2F velocity;
	point2F steering;
	float mass;

	point2F seek(point2F target, float slowingRadius);

	point2F flee(point2F position);

	void update();

};

#endif