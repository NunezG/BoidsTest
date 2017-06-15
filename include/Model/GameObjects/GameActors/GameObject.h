
#ifndef GAMEOBJECR_H
#define GAMEOBJECR_H

#include "Model\GameObjects\TeamObject.h"
#include "Model\GameObjects\Flag.h"

//#include "../Renderer/D2DHelper.h"
#include "Model\agentbrainlib.h"
//#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
//#include "../SimpleDirect2dApplication.h"

//using namespace std;

//class CGameState;


class CGameObject : public CTeamObject
{
protected:
	Vector2d m_position;

public:
	
	CGameObject(Vector2d position, ETeam team) :
		CTeamObject(team),
		m_position(position)
	{
		
	}
	CGameObject(){}
	Vector2d getPosition() const { return m_position; }
	float getPosX() const { return m_position.m_x; }
	float getPosY() const { return m_position.m_y; }

	// static routines
	static float agentDistance(const CGameObject *agent1, const CGameObject *agent2) { return (agent1->getPosition() - agent2->getPosition()).length(); }
	static float sqrAgentDistance(const CGameObject *agent1, const CGameObject *agent2) { return (agent1->getPosition() - agent2->getPosition()).sqrLength(); }

//	bool IsAtStartLocation() const;
	
	

protected:


	float m_fCollisionRadius;



};


#endif
