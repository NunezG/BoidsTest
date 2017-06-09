

#ifndef BRAIN_H
#define BRAIN_H

#include "../../GameObjects/GameObject.h"
#include "../StackFSM.h"
//FSM


class Brain : public StackFSM
{

public:

	point2F seek(point2F target, float slowingRadius);

	point2F flee(point2F position);

	void update();

};

#endif