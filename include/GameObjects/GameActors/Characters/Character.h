
#ifndef CHARACTER_H
#define CHARACTER_H

//#include "../Flag.h"
//#include "../../FSM/Characters/characterState.h"
//#include "Boid.h"
//#include "../../FSM/Characters/Brain.h"
#include "GameObjects\GameActors\GameObject.h"
#include <vector>
#include "GameObjects\GameActors\StartPosition.h"

//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

class CBoid;
class CCharacterState;
class CBrain;
class CFlagStand;


class CCharacter : public CGameObject
{

private:
	bool m_bAlive;

public:
	
	CCharacter(CFlagStand* TeamStand);
	
	CCharacter();

//	bool DropFlag(point2F fCurrentLocation);

//	bool getFlag(Flag flag);

	//FSM
	void ChangeState(CCharacterState* state);
	void PushState(CCharacterState* state);
	void PopState();

	//static void Update();

//	void findLeaf();

	//Pool
	CCharacter* getNext() const { return /*m_sState.m_sDead.*/nextDeadCharacter; }
	void setNext(CCharacter* next) { /*m_sState.m_sDead.*/nextDeadCharacter = next; }

	void Update();

	bool isAlive() const { return m_bAlive; }

	void Init(float x, float y)
	{		
		//CGameObject::Init(x, y);
		m_bAlive = true;

	}

	void Die();

	void Spawn();

	


private:
	const int RANDOM_SPAWN = 60;

	const float DETECTION_RADIUS = 5.0f;
	const float RESPAWN_SECONDS = 5;
	float respawnTimer;


	// the stack of states
	std::vector<CCharacterState*> states;

	//point2F m_fVelocity;

	CBoid* boid;
	CBrain* brain;

	//union
//	{

	
		// State when it's in use.
//		struct
//		{


			//double x, y;
			point2F* m_fVelocity;
			//point2F m_fAcceleration;


//		} m_sLive;

//		struct
//		{
			float m_fDeadTimer;

			//ifdead
			CCharacter* nextDeadCharacter;
//		} m_sDead;


//	} m_sState;


	//} state_;

			CFlagStand* m_pFlagStand;

};

#endif
