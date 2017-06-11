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

class CFlagStand : public CGameObject
{
public:

	CFlagStand(point2F position, ETeam team);

	


private:


	float m_fApparitionRadius;

	CFlag* ownedFlag;
};

#endif
