#ifndef FLAGSTAND_H
#define FLAGSTAND_H

#include "GameObjects/GameActors/GameObject.h"

//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"
class CFlag;

//using namespace std;

//class CGameState;
#include "gameManager.h"

class CFlagStand : public CGameObject
{
public:

	CFlagStand(Vector2d position, ETeam team);

	

private:


	float m_fApparitionRadius;

	CFlag* ownedFlag;
};

#endif
