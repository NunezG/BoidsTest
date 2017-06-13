

#ifndef BRAIN_H
#define BRAIN_H

#include "GameObjects/GameActors/GameObject.h"
#include "StackFSM.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\characterState.h"

//FSM


class CBrain : public StackFSM
{

public:

	Vector2d seek(Vector2d target, float slowingRadius);

	Vector2d flee(Vector2d position);

	void update();




};

#endif