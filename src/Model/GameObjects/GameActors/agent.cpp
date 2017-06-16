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
	
		

     //   m_position.clamp(Vector2d(0.0f, 0.0f), Vector2d(1.0f, 1.0f)); // cannot go outside world borders
    
}

///////////////////////////////////////////////////////////////////
// CAgent::initialize
// set everything to 0, randomize start position, activate
///////////////////////////////////////////////////////////////////
void CAgent::initialize(Vector2d startPosition) {

	respawnTimer = 0;

	m_active = true;

	CFlagSeekState* state = new CFlagSeekState(this, m_TargetFlag, m_pFlagStand);

	m_brain->PushState(state);

	float randomX = (float)(rand() % (60 * 2 + 1) - 60);
	float randomY = (float)(rand() % (60 * 2 + 1) - 60);
	
	m_velocity = Vector2d(0.0f, 0.0f);
	setSteer(Vector2d(0.0f, 0.0f));
    setEnemy(NULL);
    m_position = Vector2d(startPosition.m_x + randomX, startPosition.m_y + randomY);
    m_active = true;
  //  makeBrain();
}

///////////////////////////////////////////////////////////////////
// CAgent::getSeparationSteer
// nearby agent avoidance, used in flocking
///////////////////////////////////////////////////////////////////
Vector2d CAgent::getSeparationSteer(float radius, float angle) const {
    Vector2d result(0.0f, 0.0f);
    for (std::list <CAgent*>::iterator _agent = g_game->m_agents.begin(); _agent != g_game->m_agents.end(); _agent++) {
            CAgent *agent = (*_agent);
            if (agent->m_active && isNeighbour(agent, radius, angle)) {
                Vector2d dx = this->getPosition() - agent->getPosition();
                float length = dx.length();
                if (length > 0) {
                    dx.scale(1.0f / (length * length));
					//CD2DHelper::ShowNum(result.m_x, 3);

                }
                result = result + dx;

            }
    }

    return result;
}

///////////////////////////////////////////////////////////////////
// CAgent::getCohesionSteer
// nearby agent cohesion. used in flocking
///////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////
// CAgent::getAlignmentSteer
// nearby agent velocity vector alignment. used in flocking
///////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////
// CAgent::getBordersSteer
// borders avoidance
///////////////////////////////////////////////////////////////////
Vector2d CAgent::getBordersSteer(int steepness) const {
    Vector2d result(0.0f, 0.0f);
    Vector2d position = getPosition();
    double movx = (0.5 - position.m_x) / 0.5;
    double movy = (0.5 - position.m_y) / 0.5;
    double resx = movx, resy = movy;
    for (int i = 0; i < steepness; i++) {
        resx *= movx * movx;
        resy *= movy * movy;
    }
    result = result + Vector2d((float)resx, (float)resy);
    return result;
}

///////////////////////////////////////////////////////////////////
// CAgent::isNeighbour
// agent is considered a neighbour if its within radius and inside fov
///////////////////////////////////////////////////////////////////
bool CAgent::isNeighbour(const CAgent *other, float radius, float angle) const {
    if (this == other)
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

///////////////////////////////////////////////////////////////////
// CAgent::canSee
///////////////////////////////////////////////////////////////////
bool CAgent::canSee(const CAgent *other) const {
    return sqrDistanceTo(other) < m_sight * m_sight;
}


///////////////////////////////////////////////////////////////////
// CAgent::canKill
///////////////////////////////////////////////////////////////////
bool CAgent::canDie() const {
	return enemiesSurrounding() >= m_enemiesToDie;
}

///////////////////////////////////////////////////////////////////
// CAgent::canKill
///////////////////////////////////////////////////////////////////
bool CAgent::canKill(const CAgent *other) const { 
	return (sqrDistanceTo(other) < m_attackZone * m_attackZone) && (enemiesSurrounding() < 2) && other->canDie();
}

///////////////////////////////////////////////////////////////////
// CAgent::setSteer
// sets the current steering force for the agent (m / (s^2))
///////////////////////////////////////////////////////////////////
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
	//	Vector2d velDiff = this->getSteer()* lastFrameTicks; // m / (s^2) * s = m / s

		respawnTimer -= lastFrameTicks;

	//	std::cout

		if (respawnTimer <= 0)
			initialize(m_pFlagStand->getPosition());
	}
	
	//framesLeft_--;

	//m_fCurrentLocation.X += m_fVelocity->X;
	//m_fCurrentLocation.Y += m_fVelocity->Y;

	// Update the brain. It will run the current state function.
	//brain.update();


	// Update the steering behaviors
	//	boid.update();
}



void CAgent::Die()
{
	//LooseFlag();
	m_active = false;
	respawnTimer = m_respawnSeconds;
}


CAgent * CAgent::findNearestVisibleEnemy() {
	CAgent *bestAgent = NULL;
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