#ifndef FLAG_H
#define FLAG_H

#include "GameObjects\TeamObject.h"
//#include "Characters\Character.h"
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

	//CCharacter OwnedBy() const;

	//bool setOwner(CCharacter owner);


private:

	CGameObject* m_currentOwner;

};

#endif
