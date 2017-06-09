
#ifndef CHARACTER_H
#define CHARACTER_H

//#include "../Flag.h"
#include "../../FSM/Characters/characterState.h"
#include "Boid.h"
#include "../../FSM/Characters/Brain.h"
#include "../GameObject.h"
//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//class CGameState;

class CCharacter : public CGameObject
{
public:
	
	CCharacter() {

		// Tell the brain to start looking for the leaf.
		//	brain->pushState(findLeaf);

	}

	bool m_bHasTheFlag;


//	bool DropFlag(point2F fCurrentLocation);

//	bool getFlag(Flag flag);

	//FSM
	void ChangeState(CCharacterState* state);
	void PushState(CCharacterState* state);
	void PopState();

	//static void Update();

//	void findLeaf();

private:

	// the stack of states
	std::vector<CCharacterState*> states;

	bool m_bAlive;

	float m_fDetectionRadius;

	point2F m_fVelocity;

	point2F m_fAcceleration;

	Boid* boid;
	Brain* brain;

};

#endif
