
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <list>

//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../gameManager.h"

#include "Model\GameObjects\GameActors\StartPosition.h"
#include "GameActors\agent.h"
#include "Model\GameObjects\Flag.h"
#include "Model\virtualtime.h"

using namespace std;

class CObjectManager;

//class CGameState;
extern CObjectManager *g_model;


class CObjectManager
{

public:
	// the stack of states
	 const int LIONS_NUMBER = 5;
	 const int ANTELOPES_NUMBER = 30;
	 const int POOL_NUMBER = LIONS_NUMBER + ANTELOPES_NUMBER;


public:

//	 ~CObjectManager();

	 void Init();

	 void Cleanup();

//	 void ChangeState(CGameState* state);
//	 void PushObject(CGameState* state);
//	 void PopObject();

//	 void HandleEvents(UINT message);
	 void Update();


//	 void Draw(ID2D1HwndRenderTarget* renderTarget);
//	 void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

	// bool Running() { return m_running; }
	// void Quit() { m_running = false; }

	//SDL_Surface* screen;
	// void spawnCharacter(ETeam team, double x, double y, double xVel, double yVel);

	// void spawnLion(double x, double y, double xVel, double yVel);

	//Create flag and stand
	 void spawnFixedObject(double x, double y, ETeam team);

	// CCharacterFSM m_aCharacters[LIONS_NUMBER + ANTELOPES_NUMBER];
	// CCharacterFSM* m_oCharacters[ANTELOPES_NUMBER + LIONS_NUMBER];
	// Lion m_oLions[LIONS_NUMBER];


	
	 bool CheckIfDead(CAgent* character);

	
	 int updateAI(TRealTime maxTime);




	 std::list <CAgent* > m_agents;
	 CFlagStand stands[2];
	 CFlag* m_pFlags[2];

	 int registerAgent(ETeam team);

private:


	

	// CCharacterFSM* m_pFirstDeadCharacter;

	//non-charqcter objects (flags and stands)
//	 CGameObject* m_OObjects[4];

	 bool m_fullscreen;





};

#endif
