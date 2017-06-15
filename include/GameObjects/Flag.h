#ifndef FLAG_H
#define FLAG_H

#include "GameObjects\TeamObject.h"
//#include "GameObjects\GameActors\GameObject.h"
//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;
class CGameObject;

class CFlag : public CTeamObject
{
public:

	CFlag(ETeam team, CGameObject* owner);

	//bool IsAtenemyHome() const;

	CGameObject* getOwner() const;
	void setOwner(CGameObject* owner)
	{
		//owner->ReceiveFlag(this);
		m_currentOwner = owner;
	}


private:

	CGameObject* m_currentOwner;

};

#endif
