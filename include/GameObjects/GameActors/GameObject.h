
#ifndef GAMEOBJECR_H
#define GAMEOBJECR_H

#include "GameObjects\TeamObject.h"
#include "GameObjects\Flag.h"

//#include "../Renderer/D2DHelper.h"
#include "gameManager.h"
//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//class CGameState;


class CGameObject : public CTeamObject
{
public:
	
	CGameObject(Vector2d position, ETeam team) :
		CTeamObject(team),
		m_pFlag(nullptr),
		initialPosition(position)
	{
		
	}
	

//	bool IsAtStartLocation() const;
	
	bool HasFlag() const
	{
		return m_pFlag != nullptr;
	}

	CFlag* getFlag() const
	{
		if (m_pFlag)
		return m_pFlag;
		else return nullptr;
	}

	void ReceiveFlag(CFlag* flag)
	{
		m_pFlag = flag;
	}

	void LooseFlag()
	{
		m_pFlag = nullptr;
	}

	Vector2d initialPosition;


protected:


	float m_fCollisionRadius;

	CFlag* m_pFlag;


};


#endif
