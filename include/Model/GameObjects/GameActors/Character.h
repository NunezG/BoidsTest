
#ifndef CHARACTER_H
#define CHARACTER_H

//#include "../Flag.h"
//#include "../../FSM/Characters/characterState.h"
//#include "Boid.h"
//#include "../../FSM/Characters/Brain.h"
//#include "GameObjects\GameActors\GameObject.h"
#include <vector>
//#include "GameObjects\GameActors\StartPosition.h"

//#include "introstate.h"
//#include "menustate.h"
#include "ActorFSM\stateBase.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//#include "agent.h"

//class CBoid;
//class CCharacterFSMState;
class CBrain;
//class CFlagStand;
//class CStateBase;


class CCharacterFSM
{

private:
	//bool m_bAlive;

public:
		
	CCharacterFSM() {}
//	bool DropFlag(point2F fCurrentLocation);

//	bool getFlag(Flag flag);

	//FSM
	void ChangeState(CStateBase* state);
	void PushState(CStateBase* state);
	void PopState();
	CStateBase* getCurrentState() const;
	void Update()
	{
		CStateBase* currentStateFunction = getCurrentState();
		if (currentStateFunction != nullptr) {
			currentStateFunction->Update();
		}

	}

//	void findLeaf();

	//Pool
	CCharacterFSM* getNext() const { return /*m_sState.m_sDead.*/nextDeadCharacter; }
	void setNext(CCharacterFSM* next) { /*m_sState.m_sDead.*/nextDeadCharacter = next; }



	void Init(float x, float y)
	{		
		//CGameObject::Init(x, y);
	}



	int processAgentConstant() { return 0; }
	 int processAgentPeriodic() { return 0; }


	 void drawAgent() const{}

protected:


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
			CCharacterFSM* nextDeadCharacter;
//		} m_sDead;


//	} m_sState;


	//} state_;

		
		

};

#endif
