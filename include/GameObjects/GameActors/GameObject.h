
#ifndef GAMEOBJECR_H
#define GAMEOBJECR_H

#include "GameObjects\TeamObject.h"
#include "GameObjects\Flag.h"

//#include "../Renderer/D2DHelper.h"

//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//class CGameState;

struct point2F
{
public:

	float X; //maybe double?
	float Y;

	point2F() : X(0.0f) 
			, Y(0.0f)
	{}

	point2F(float x, float y) :
		X(x)
		, Y(y)
	{}
};



class CGameObject : public CTeamObject
{
public:
	
	CGameObject(point2F position, ETeam team) :
		CTeamObject(team),
		m_fCurrentLocation(position)
	{
		
	}

	CGameObject() : m_fCurrentLocation(point2F())
	{

	}

	point2F GetLocation() const 
	{
		return m_fCurrentLocation;
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

protected:

	point2F m_fCurrentLocation;

	float m_fCollisionRadius;

	CFlag* m_pFlag;


};


#endif
