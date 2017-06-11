

#ifndef BRAIN_H
#define BRAIN_H

#include "GameObjects/GameActors/GameObject.h"
#include "StackFSM.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\characterState.h"

//FSM


class CBrain : public StackFSM
{

public:

	point2F seek(point2F target, float slowingRadius);

	point2F flee(point2F position);

	void update();




};

#endif