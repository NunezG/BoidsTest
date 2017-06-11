
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
	lionsTeam,
	antelopesTeam
};


enum EobjectType
{
	Flag,
	Stand,
	Character
};

class CTeamObject
{
public:
	
	CTeamObject(ETeam team) : m_eObjectTeam(team)
	{
	}

	CTeamObject()
	{

	}

	void SetTeam(ETeam team);
	ETeam GetTeam() const { return m_eObjectTeam; }

	bool IsOfTeam(ETeam team) const { return m_eObjectTeam == team; }


//	bool IsAtStartLocation() const;


private:

	ETeam m_eObjectTeam;

};

#endif
