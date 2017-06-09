
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//#include "../Renderer/D2DHelper.h"

//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//class CGameState;

enum ETeam
{
	lionsteam,
	antelopesTeam
};

struct point2F
{
	float X;
	float Y;


	point2F() : X(0) 
			, Y(0)
	{
	}

	point2F(float x, float y)
	{
		X = x;
		Y = y;
	}
};

class CGameObject
{
public:
	
	CGameObject()
	{


	}
//	bool GetLocation() const;

//	bool IsAtStartLocation() const;

	


private:

	point2F m_fCurrentLocation;

	point2F m_fStartLocation;

	float m_fCollisionRadius;

	ETeam team;

};

#endif
