
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

//#include "agent.h"

//class CBoid;
//class CCharacterState;
class CBrain;
//class CFlagStand;
class CStateBase;

struct characterStats
{
	float speed;
	float respawnTime;
	float cohesion;

};

class CCharacter : public CGameObject
{

private:
	//bool m_bAlive;

public:
	
	CCharacter(CFlagStand* TeamStand, CFlag* enemyFlag);
	
	CCharacter() {}
//	bool DropFlag(point2F fCurrentLocation);

//	bool getFlag(Flag flag);

	//FSM
	void ChangeState(CStateBase* state);
	void PushState(CStateBase* state);
	void PopState();
	CStateBase* getCurrentState() const;
	//static void Update();

//	void findLeaf();

	//Pool
	CCharacter* getNext() const { return /*m_sState.m_sDead.*/nextDeadCharacter; }
	void setNext(CCharacter* next) { /*m_sState.m_sDead.*/nextDeadCharacter = next; }



	void Init(float x, float y)
	{		
		//CGameObject::Init(x, y);
	}



	int processAgentConstant() { return 0; }
	 int processAgentPeriodic() { return 0; }
	 void drawAgent() const{}

protected:

	const float DETECTION_RADIUS = 5.0f;
	const float RESPAWN_SECONDS = 5;
	float respawnTimer;


	// the stack of states
	std::vector<CStateBase*> states;

	//point2F m_fVelocity;

//	CBoid& boid;
	//CBrain& brain;

	//union
//	{

	
		// State when it's in use.
//		struct
//		{


			//double x, y;
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

		
		

};

#endif
