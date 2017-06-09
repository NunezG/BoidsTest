#ifndef FLAG_H
#define FLAG_H

//#include "Characters\Character.h"
//#include "Characters\Character.h"
//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
#include "GameObject.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//class CGameState;

class CCharacter;

class Flag : public CGameObject
{
public:

	//bool IsAtenemyHome() const;

	//CCharacter OwnedBy() const;

	//bool setOwner(CCharacter owner);


private:

	CCharacter* m_currentOwner;


};

#endif
