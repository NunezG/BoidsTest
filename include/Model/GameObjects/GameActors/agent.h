#ifndef _myagentw_h_
#define _myagentw_h_

#include <math.h>
//#include "game.h"
#include "Model\virtualtime.h"

#include "Model\GameObjects\GameActors\CharacterFSM.h"

#include "Model\game.h"

///////////////////////////////////////////////////////////////////
// CAgent
// abstract base class for agents.
// extends CAgent, meaning each agent can have its own brain
///////////////////////////////////////////////////////////////////
class CAgent : public CGameObject {

private:
	float respawnTimer;
	Vector2d m_steer;
	Vector2d m_velocity;
protected:
	float m_sight;
	float m_attackZone;
	float m_maxSpeed;
	float m_respawnSeconds;
	int m_enemiesToDie;

	CAgent *m_enemy;

public:
	CAgent(CFlagStand* TeamStand, CFlag* enemyFlag) :
		CGameObject(TeamStand->getPosition(), TeamStand->GetTeam())
		, m_brain(new CCharacterFSM())
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
	//bool m_marked;
	void setSteer(const Vector2d & steer);
	void setEnemy(CAgent * nmy) { m_enemy = nmy; }
	void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }

	// engine routines
	int processAgentConstant()
	{
		move();
		return 0;
	}



	int processAgentPeriodic() {
		m_brain->Update();
		return 0;
	}

	//virtual void drawAgent() const = 0;
	void move();

	// agent status query routines; no changes allowed (consts)
	float getMaxSpeed() const { return m_maxSpeed; }
	float getSpeed() const { return m_velocity.length(); }
	Vector2d getSteer() const { return m_steer; }
	
	Vector2d getVelocity() const { return m_velocity; }
	Vector2d getCohesionSteer(float, float) const;
	Vector2d getSeparationSteer(float, float) const;
	Vector2d getAlignmentSteer(float, float) const;
	Vector2d getBordersSteer(int) const;
	
	bool canSee(const CAgent *other) const;
	bool canKill(const CAgent *other) const;
	int enemiesSurrounding() const;

	bool isNeighbour(const CAgent *other, float radius, float angle) const;
	CAgent * getEnemy() const { return m_enemy; }

	CFlagStand* m_pFlagStand;
	CFlag* m_TargetFlag;

	CCharacterFSM* m_brain;

	EObjectType objectType()
	{
		return EObjectType::Agent;
	}

	CAgent * findNearestVisibleEnemy();

	bool canDie() const;
	int enemiesAtAttackDistance() const;


};
///////////////////////////////////////////////////////////////////

#endif
