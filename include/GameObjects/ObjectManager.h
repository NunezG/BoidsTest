
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../gameManager.h"

#include "GameObjects\GameActors\StartPosition.h"
#include "GameObjects/GameActors/Characters/Character.h"
#include "GameObjects\Flag.h"


using namespace std;

//class CGameState;


class CObjectManager
{

public:
	// the stack of states
	static const int LIONS_NUMBER = 0;
	static const int ANTELOPES_NUMBER = 30;
	static const int POOL_NUMBER = LIONS_NUMBER + ANTELOPES_NUMBER;


public:

//	static ~CObjectManager();

	static void Init();

	static void Cleanup();

//	static void ChangeState(CGameState* state);
//	static void PushObject(CGameState* state);
//	static void PopObject();

//	static void HandleEvents(UINT message);
	static void Update();


//	static void Draw(ID2D1HwndRenderTarget* renderTarget);
//	static void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

	//static bool Running() { return m_running; }
	//static void Quit() { m_running = false; }

	//SDL_Surface* screen;
	//static void spawnCharacter(ETeam team, double x, double y, double xVel, double yVel);

	//static void spawnLion(double x, double y, double xVel, double yVel);

	//Create flag and stand
	static void spawnFixedObject(double x, double y, ETeam team);

	//static CCharacter m_aCharacters[LIONS_NUMBER + ANTELOPES_NUMBER];
	//static CCharacter* m_oCharacters[ANTELOPES_NUMBER + LIONS_NUMBER];
	//static Lion m_oLions[LIONS_NUMBER];


	static CFlagStand* stands[2];

	static CFlag* m_pFlags[2];
	static bool CheckIfDead(CCharacter* character);

	static int registerAgent(CAgent *);
	static int updateAI(TRealTime maxTime);
	static int buildFrameConstant();
	static std::list <CAgent *> m_agents;

private:


	

	//static CCharacter* m_pFirstDeadCharacter;

	//non-charqcter objects (flags and stands)
//	static CGameObject* m_OObjects[4];

	static bool m_fullscreen;





};

#endif
