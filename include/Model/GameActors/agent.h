#ifndef _myagentw_h_
#define _myagentw_h_

#include <math.h>

#include "Model\virtualtime.h"
#include "Model\GameActors\CharacterFSM.h"
#include "Model\game.h"



class CAgent : public CGameObject {

private:
	float respawnTimer;
	Vector2d m_steer;
	Vector2d m_velocity;
protected:
	float m_sight;
	float m_attackZone;
	float m_killZone;
	float m_maxSpeed;
	float m_respawnSeconds;

	CAgent *m_enemy;

	float m_separationRadius;
	float m_cohesionRadius;
	float m_alignmentRadius;

	float m_separationForce;
	float m_cohesionForce;
	float m_alignmentForce;
	CFlagStand* m_pFlagStand;

public:

	int m_enemiesToDie;

	CAgent(CFlagStand* flagStand, CFlag* enemyFlag);

	~CAgent();

	void Update();
	void Die();

	void initialize(Vector2d flagStand);

	bool m_active;
	bool m_done;
	void setSteer(const Vector2d & steer);
	void setEnemy(CAgent * nmy) { m_enemy = nmy; }
	void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }

	void move();

	// agent status query routines; no changes allowed (consts)
	float getMaxSpeed() const { return m_maxSpeed; }
	float getSpeed() const { return m_velocity.length(); }
	Vector2d getSteer() const { return m_steer; }
	Vector2d getVelocity() const { return m_velocity; }
	Vector2d getCohesionSteer(float, float) const;
	Vector2d getSeparationSteer(float, float) const;
	Vector2d getAlignmentSteer(float, float) const;
	Vector2d getBordersSteer() const;	
	bool canSee(const CAgent *other) const;
	bool canAttack(const CAgent *other) const;
	bool canKill(const CAgent *other) const;
	int enemiesSurrounding() const;
	int enemiesAtAttackDistance() const;
	int enemiesAtKillDistance() const;
	bool isAtAttackDistance(const CAgent *other) const;
	bool isNeighbour(const CAgent *other, float radius, float angle) const;
	CAgent * getEnemy() const { return m_enemy; }
	EObjectType objectType() const { return EObjectType::Agent; }
	CAgent * findNearestVisibleEnemy() const;
	bool canDie() const;
	Vector2d getDirection() const { return m_velocity; }
	CFlagStand* getFlagStand() const { return m_pFlagStand; }

	CFlag* m_TargetFlag;
	CCharacterFSM* m_brain;

	Vector2d Seek(Vector2d target);
	Vector2d Attack(Vector2d target);
	Vector2d Avoid(Vector2d target);
};

#endif
