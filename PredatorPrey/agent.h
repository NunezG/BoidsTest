#ifndef _myagentw_h_
#define _myagentw_h_

#include <math.h>
#include "gameManager.h"
//#include "game.h"
#include "virtualtime.h"

#include "GameObjects\GameActors\Characters\Character.h"

#include "game.h"

///////////////////////////////////////////////////////////////////
// CAgent
// abstract base class for agents.
// extends CAgent, meaning each agent can have its own brain
///////////////////////////////////////////////////////////////////
class CAgent :  public CCharacter{

private:
	Vector2d m_steer;
	Vector2d m_velocity;
protected:
	TVirtTime m_lastUpdate;
	float m_walkSpeed;
	float m_sight;
	float m_maxSpeed;
	CAgent *m_enemy;
public:
	CAgent(CFlagStand* TeamStand, CFlag* enemyFlag): 
		CCharacter(TeamStand, enemyFlag)
		, m_active(true) 
		, m_pFlagStand(TeamStand)
		//, brain(CBrain())
		, m_TargetFlag(enemyFlag)
	
	{
	
	}


	CFlagStand* getFlagStand() const {
		return m_pFlagStand;
	}

	void Update();
	void Die();

//	virtual ~CAgent() {}
	void initialize(Vector2d startPosition);

	// non-physical stats (changeable by user)
	bool m_active;
	bool m_done;
	bool m_marked;
	void setSteer(const Vector2d & steer);
	void setEnemy(CAgent * nmy) { m_enemy = nmy; }
	void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }

	// engine routines
	virtual int processAgentConstant() = 0;
	virtual int processAgentPeriodic() = 0;
	//virtual void drawAgent() const = 0;
	void move();

	// agent status query routines; no changes allowed (consts)
	float getMaxSpeed() const { return m_maxSpeed; }
	float getSpeed() const { return m_velocity.length(); }
	float getWalkSpeed() const { return m_walkSpeed; }
	Vector2d getSteer() const { return m_steer; }
	
	Vector2d getVelocity() const { return m_velocity; }
	Vector2d getCohesionSteer(float, float) const;
	Vector2d getSeparationSteer(float, float) const;
	Vector2d getAlignmentSteer(float, float) const;
	Vector2d getBordersSteer(int) const;
	float distanceTo(const CAgent *other) const { return agentDistance(this, other); }
	float sqrDistanceTo(const CAgent *other) const { return sqrAgentDistance(this, other); }
	bool canSee(const CAgent *other) const;
	bool isNeighbour(const CAgent *other, float radius, float angle) const;
	CAgent * getEnemy() const { return m_enemy; }

	CFlagStand* m_pFlagStand;
	CFlag* m_TargetFlag;


};
///////////////////////////////////////////////////////////////////

#endif
