#ifndef FLAG_H
#define FLAG_H

//#include "Model\GameObjects\TeamObject.h"
#include "Model\GameObjects\GameActors\GameObject.h"
#include "Model\GameObjects\GameActors\StartPosition.h"

//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;
class CAgent;
class CFlagStand;

enum EFlagState
{
	flriendlyStand,
	enemyStand,
	friendlyAgent,
	enemyAgent
};

class CFlag : public CGameObject
{
public:

	CFlag(ETeam team, CGameObject* owner, CFlagStand* friendlyStand);

	//bool IsAtenemyHome() const;
	EObjectType objectType()
	{
		return EObjectType::Flag;
	}

	CGameObject* getOwner() const;

	void setOwner(CGameObject* owner)
	{
		
		//owner->ReceiveFlag(this);
		m_currentOwner = owner;
		//pointRule();
	}

	bool pointRule()
	{

		
		if ((getOwner()->getPosition() - m_friendlyStand->getPosition()).length() < 50)
			return true;

		return false;
	}


	CFlagStand* m_friendlyStand;


	EFlagState getState() const { return m_currentState; }

private:


	EFlagState m_currentState;

	CGameObject* m_currentOwner;



};

#endif
