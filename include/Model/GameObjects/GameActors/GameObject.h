
#ifndef GAMEOBJECR_H
#define GAMEOBJECR_H

//#include "../Renderer/D2DHelper.h"
#include "Model\agentbrainlib.h"
//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//class CGameState;

enum EObjectType 
{
	Flag,
	Agent,
	Stand
};

enum ETeam
{
	lionsTeam,
	antelopesTeam
};


class CGameObject 
{
protected:
	Vector2d m_position;

public:
	
	CGameObject(Vector2d position, ETeam team) :
		m_eObjectTeam(team)
	, m_position(position)
	{
		
	}
	CGameObject(){}
	Vector2d getPosition() const { return m_position; }
	float getPosX() const { return m_position.m_x; }
	float getPosY() const { return m_position.m_y; }

	// static routines
	static float agentDistance(const CGameObject *agent1, const CGameObject *agent2) { return (agent1->getPosition() - agent2->getPosition()).length(); }
	static float sqrAgentDistance(const CGameObject *agent1, const CGameObject *agent2) { return (agent1->getPosition() - agent2->getPosition()).sqrLength(); }
	float distanceTo(const CGameObject *other) const { return agentDistance(this, other); }
	float sqrDistanceTo(const CGameObject *other) const { return sqrAgentDistance(this, other); }
//	bool IsAtStartLocation() const;
	
	virtual EObjectType objectType() = 0;

	void SetTeam(ETeam team) { m_eObjectTeam = team; }
	ETeam GetTeam() const { return m_eObjectTeam; }

	bool IsOfTeam(ETeam team) const { return m_eObjectTeam == team; }

protected:


	float m_fCollisionRadius;

	ETeam m_eObjectTeam;


};


#endif
