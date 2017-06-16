////////////////////////////////////////////////////////////////////////////////
// file: agent.cpp
// author: Radim Rehurek
// last update: 25.09.04
//
// abstract base class for agents
//////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <cassert>
#include <list>

#include "Model\GameObjects\GameActors\agent.h"
#include "Model\virtualtime.h"
#include "Model\GameObjects\GameActors\ActorFSM\FlagSeekState.h"

///////////////////////////////////////////////////////////////////
// CAgent::move
// adjust agent's position, taking into account the simulation time elapsed since last frame
///////////////////////////////////////////////////////////////////
void CAgent::move() {

    const float MAX_SPEED = 40.0f;
    TVirtTime lastFrameTicks = g_game->m_time->lastFrameTicks();
	Vector2d velDiff = this->getSteer()* lastFrameTicks; // m / (s^2) * s = m / s
    this->m_velocity = this->m_velocity + velDiff; // m / s + m / s
	
    if (this->getSpeed() > this->getMaxSpeed()) // cannot exceed agent's maximal velocity
        m_velocity.stretchTo(this->getMaxSpeed());
    if (this->getSpeed() > MAX_SPEED) // cannot exceed physical barrier for speed
        m_velocity.stretchTo(MAX_SPEED);
	

	Vector2d posDiff = this->m_velocity* lastFrameTicks; // m / s * s = m
        m_position = m_position + posDiff; // m + m
	    
}

void CAgent::initialize(Vector2d startPosition) {

	printf("AGENT INITIALIZE \n");
	respawnTimer = 0;

	m_active = true;

	float randomX = (float)(rand() % (180 * 2 + 1) - 180);
	float randomY = (float)(rand() % (180 * 2 + 1) - 180);
	
	m_velocity = Vector2d(0.0f, 0.0f);
	setSteer(Vector2d(0.0f, 0.0f));
    setEnemy(NULL);
    m_position = Vector2d(startPosition.m_x + randomX, startPosition.m_y + randomY);
    m_active = true;

	m_brain->Init();

	CFlagSeekState* state = new CFlagSeekState(this, m_TargetFlag, m_pFlagStand);
	m_brain->PushState(state);


}


Vector2d CAgent::getSeparationSteer(float radius, float angle) const {
    Vector2d result(0.0f, 0.0f);
    for (std::list <CAgent*>::iterator _agent = g_game->m_agents.begin(); _agent != g_game->m_agents.end(); _agent++) {
            CAgent *agent = (*_agent);
            if (agent->m_active && isNeighbour(agent, radius, angle)) {
                Vector2d dx = this->getPosition() - agent->getPosition();
                float length = dx.length();
                if (length > 0) {
                    dx.scale(1.0f / (length * length));

                }
                result = result + dx;

            }
    }

    return result;
}


Vector2d CAgent::getCohesionSteer(float radius, float angle) const {
    Vector2d result(0.0f, 0.0f);
    int cnt = 0;
    for (std::list <CAgent*>::iterator _agent = g_game->m_agents.begin(); _agent != g_game->m_agents.end(); _agent++) {
            CAgent *agent = (*_agent);
            if (agent->m_active && isNeighbour(agent, radius, angle)) {
                result = result + agent->getPosition();
                cnt++;
            }
    }
    if (cnt > 0) {
        result.scale(1.0f / cnt);
        result = result - getPosition();
    }
    return result;
}


Vector2d CAgent::getAlignmentSteer(float radius, float angle) const {
    Vector2d result(0.0f, 0.0f);
    int cnt = 0;
    for (std::list <CAgent*>::iterator _agent = g_game->m_agents.begin(); _agent != g_game->m_agents.end(); _agent++) {
            CAgent *agent = (*_agent);
            if (agent->m_active && isNeighbour(agent, radius, angle)) {
                Vector2d dx(agent->getVelocity());
                dx.normalize();
                result = result + dx;
                cnt++;
            }
    }
    if (cnt > 0) {
        result.scale(1.0f / cnt);
        result = result - this->getVelocity();
    }
    return result;
}

//Border avoidance
Vector2d CAgent::getBordersSteer(int steepness) const {
    Vector2d result(0.0f, 0.0f);
	Vector2d position = getPosition();

	if (position.m_y > 800)
		position.m_y = 800;

	if (position.m_x > 800)
		position.m_x = 800;

	if (position.m_y < 0)
		position.m_y = 0;

	if (position.m_x < 0)
		position.m_x = 0;

	result = position - getPosition();

	result.scale(50);

    return result;
}

///////////////////////////////////////////////////////////////////
// CAgent::isNeighbour
// agent is considered a neighbour if its within radius and inside fov
///////////////////////////////////////////////////////////////////
bool CAgent::isNeighbour(const CAgent *other, float radius, float angle) const {
    if (this == other )//|| !IsOfTeam(other->GetTeam()))
        return false;
    Vector2d dx = other->getPosition() - this->getPosition();
    if (dx.sqrLength() > radius * radius)
        return false; // is too far away?
    Vector2d sx = this->getVelocity();
    float ang0 = atan2f(-sx.m_y, sx.m_x);
    Vector2d nx(cosf(ang0) * dx.m_x - sinf(ang0) * dx.m_y, sinf(ang0) * dx.m_x + cosf(ang0) * dx.m_y);
    float ang1 = atan2f(-nx.m_y, nx.m_x);
    return fabsf(ang1) <= angle; // is inside fov?
}

bool CAgent::canSee(const CAgent *other) const {
    return sqrDistanceTo(other) < m_sight * m_sight;
}


bool CAgent::canDie() const {
	CAgent* enemy = findNearestVisibleEnemy();

	bool enemySurrounded = false;

	if (enemy && enemy->enemiesAtAttackDistance() >= 2)
	{
		enemySurrounded = true;
	}

	return enemiesAtKillDistance() >= m_enemiesToDie;//&& !enemySurrounded;
	 
}

bool CAgent::canAttack(const CAgent *other) const
{

	bool isSurrounded = false;

	bool enemySurrounded = false;


	if (other->enemiesAtAttackDistance() >= other->m_enemiesToDie)
	{
		enemySurrounded = true;
	}

	return isAtAttackDistance(other) && !isSurrounded && enemySurrounded;
}


bool CAgent::isAtAttackDistance(const CAgent *other) const
{
	return (sqrDistanceTo(other) < m_attackZone * m_attackZone);
}

bool CAgent::canKill(const CAgent *other) const { 
	return (sqrDistanceTo(other) < m_killZone * m_killZone);
}

void CAgent::setSteer(const Vector2d & steer) {
    const float MAX_FORCE = 10.0f;
    m_steer = steer;
    m_steer.truncate(MAX_FORCE);
}


int CAgent::enemiesSurrounding() const
{
	int number = 0;

	for (std::list <CAgent* >::iterator agent = g_game->m_agents.begin(); agent != g_game->m_agents.end(); agent++) {
		CAgent* _agent = *agent;

		if (_agent->GetTeam() != GetTeam() && _agent->m_active) {
			if (canSee(_agent)) {
				number++;
			}
		}
	}


	return number;

}


int CAgent::enemiesAtAttackDistance() const
{
	int number = 0;

	for (std::list <CAgent* >::iterator agent = g_game->m_agents.begin(); agent != g_game->m_agents.end(); agent++) {
		CAgent* _agent = *agent;

		if (_agent->GetTeam() != GetTeam() && _agent->m_active) {
			if (isAtAttackDistance(_agent)) {
				number++;
			}
		}
	}


	return number;

}



int CAgent::enemiesAtKillDistance() const
{
	int number = 0;

	for (std::list <CAgent* >::iterator agent = g_game->m_agents.begin(); agent != g_game->m_agents.end(); agent++) {
		CAgent* _agent = *agent;

		if (_agent->GetTeam() != GetTeam() && _agent->m_active) {
			if (_agent->canKill(this)) {
				number++;
			}
		}
	}


	return number;

}


void CAgent::Update()
{
	if (!m_active)
	{
		TVirtTime lastFrameTicks = g_game->m_time->lastFrameTicks();

		respawnTimer -= lastFrameTicks;

		if (respawnTimer <= 0)
			initialize(m_pFlagStand->getPosition());
	}
	else {


		if (canDie())
		{
			printf("DYING\n");

			Die();

				//If it owns the flag it is restored at death
				if (m_TargetFlag->getOwner() == this)
				{
					
					//get flag back to the stand
					if (IsOfTeam(ETeam::lionsTeam))
						g_game->m_pFlags[1]->setOwner(&g_game->stands[0]);
					else 
						g_game->m_pFlags[0]->setOwner(&g_game->stands[1]);


				}


		}


		m_brain->Update();


	}
	
	//framesLeft_--;

	//m_fCurrentLocation.X += m_fVelocity->X;
	//m_fCurrentLocation.Y += m_fVelocity->Y;

	// Update the brain. It will run the current state function.
	//brain.update();
//	m_brain->

	// Update the steering behaviors
	//	boid.update();
}



void CAgent::Die()
{
	m_active = false;
	respawnTimer = m_respawnSeconds;
}


CAgent * CAgent::findNearestVisibleEnemy() const {
	CAgent *bestAgent = nullptr;
	float bestDist = 1E10;
	for (std::list <CAgent* >::iterator agent = g_game->m_agents.begin(); agent != g_game->m_agents.end(); agent++) {
		CAgent* _agent = *agent;
		if (_agent->GetTeam() != GetTeam() && _agent->m_active && _agent != this) {
			float dist = this->distanceTo(_agent);
			if (dist < bestDist && canSee(_agent)) {
				bestAgent = _agent;
				bestDist = dist;
			}
		}
	}
	return bestAgent;
}


Vector2d CAgent::Seek(Vector2d target)
{

		Vector2d separation = getSeparationSteer(m_separationRadius, 2.f * M_PIf);
		//separation.normalize();
		Vector2d cohesion = getCohesionSteer(m_cohesionRadius, 2.f * M_PIf);
		cohesion.normalize();
		Vector2d alignment = getAlignmentSteer(m_alignmentRadius, 2.f * M_PIf);
		alignment.normalize();
		//        Vector2d food = m_owner->getFoodSteer(0.2f);
		//      food.normalize();

			Vector2d borders = getBordersSteer(1);
		//       borders.normalize();

		separation.scale(m_separationForce);
		cohesion.scale(m_cohesionForce);
		alignment.scale(m_alignmentForce);
		//      food.scale(1.3f);
			borders.scale(1.f);

		Vector2d delta = target - getPosition();


		//delta.normalize();
		delta.scale(0.1f);
		//	m_Owner->initialPosition;
		//float deltaX =  m_pTargetFlag->getOwner()->initialPosition.m_x - m_Owner->getPosX();
		//float deltaY = m_pTargetFlag->getOwner()->initialPosition.m_y - m_Owner->getPosY();

		//CD2DHelper::ShowNum(poisiton.m_y, 3);


		//	m_Owner->getPosition().normalize();
		//m_Owner->distanceTo(m_pTargetFlag->getOwner());

		//Vector2d vec = Vector2d(deltaX, deltaY);
		//vec.normalize();


		Vector2d dir = separation + cohesion + alignment + delta + borders;
		setSteer(dir);

		return dir;
}



Vector2d CAgent::Attack(Vector2d target)
{

	//	assert(nmy != NULL);
	//	nmy->m_marked = true;
	//	if (!nmy->m_active || !m_Owner->canSee(nmy))  // target got away
	//		return false;

	Vector2d desiredVel = target - getPosition();
	//intercept
	/*
	if (m_owner->getSpeed() > 0.001f) {
	float timeTaken = desiredVel.length() / m_owner->getSpeed();
	desiredVel = desiredVel + nmy->getVelocity() * timeTaken;
	}
	*/

	Vector2d separation = getSeparationSteer(50.f, 2.f * M_PIf);


	separation.scale(50);




	Vector2d steer = desiredVel + separation;
	steer.stretchTo(10000.0f);
	setSteer(steer);
	
	return steer;
}




Vector2d CAgent::Avoid(Vector2d target)
{
	//	assert(nmy != NULL);
	//	nmy->m_marked = true;
	//	if (!nmy->m_active || !m_Owner->canSee(nmy))  // target got away
	//		return false;

	Vector2d desiredVel = getPosition() + getDirection() - target;

	desiredVel.normalize();

	//intercept
	/*
	if (m_owner->getSpeed() > 0.001f) {
	float timeTaken = desiredVel.length() / m_owner->getSpeed();
	desiredVel = desiredVel + nmy->getVelocity() * timeTaken;
	}
	*/



	Vector2d separation = getSeparationSteer(50.f, 2.f * M_PIf);
	//separation.normalize();
	//Vector2d cohesion = m_Owner->getCohesionSteer(20, 2.f * M_PIf);
	//cohesion.normalize();
	//Vector2d alignment = m_Owner->getAlignmentSteer(20.f, 2.f * M_PIf);
	//alignment.normalize();
	//        Vector2d food = m_owner->getFoodSteer(0.2f);
	//      food.normalize();

	//	Vector2d borders = m_Owner->getBordersSteer(3);
	//        borders.normalize();

	desiredVel.scale(0.01f);
//	separation.scale(350);
	//cohesion.scale(0.1f);
	//alignment.scale(5.3f);



	//
	//	Vector2d borders = m_Owner->getBordersSteer(1);
	//        borders.normalize();


	//	borders.scale(0.1f);

	Vector2d steer = desiredVel;// + separation;// +cohesion; //+ alignment;

	steer.stretchTo(10000.0f);

	setSteer(steer);

	return steer;

}