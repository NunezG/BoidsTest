#ifndef FLAGSTAND_H
#define FLAGSTAND_H

#include "Model/GameObjects/GameActors/GameObject.h"

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

	CFlagStand(Vector2d position, ETeam team);

	CFlagStand() : CGameObject(Vector2d(0,0), ETeam::antelopesTeam)
	{


	}

	EObjectType objectType()
	{
		return EObjectType::Stand;
	}
private:


	float m_fApparitionRadius;

	CFlag* ownedFlag;
};

#endif
