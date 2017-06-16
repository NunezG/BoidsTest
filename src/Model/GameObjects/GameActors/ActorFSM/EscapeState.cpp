#include "Model\GameObjects\GameActors\ActorFSM\EscapeState.h"
#include "Model\GameObjects/GameActors/CharacterFSM.h"



void CEscapeState::Init()
{
	printf("CEscapeState InitT\n");

	m_minDirTick = 2000.0f;
	newDirection(m_minDirTick);
	m_Owner->m_done = false;

}

void CEscapeState::Cleanup()
{
//	SDL_FreeSurface(bg);
//	SDL_FreeSurface(fader);

	printf("CEscapeState Cleanup\n");
}

void CEscapeState::Pause()
{
	printf("CEscapeState Pause\n");
}

void CEscapeState::Resume()
{
	printf("CEscapeState Resume\n");
}

void CEscapeState::Update()
{
	if (m_Owner->enemiesSurrounding() < 2)
	{
		m_Owner->m_brain->PopState();

		return;
	}


	CAgent *nmy = m_Owner->getEnemy();

	//	assert(nmy != NULL);
	//	nmy->m_marked = true;
	//	if (!nmy->m_active || !m_Owner->canSee(nmy))  // target got away
	//		return false;

	Vector2d desiredVel = m_Owner->getPosition() - nmy->getPosition();
	//intercept
	/*
	if (m_owner->getSpeed() > 0.001f) {
	float timeTaken = desiredVel.length() / m_owner->getSpeed();
	desiredVel = desiredVel + nmy->getVelocity() * timeTaken;
	}
	*/



	Vector2d borders = m_Owner->getBordersSteer(1);
	//        borders.normalize();


	borders.scale(0.1f);

	Vector2d steer = desiredVel;

	steer.stretchTo(10000.0f);

	m_Owner->setSteer(steer);



	
}

void CEscapeState::newDirection(TVirtTime minTick) {
	CAgent *nmy = m_Owner->getEnemy();
//	assert(nmy != NULL);
	Vector2d n = nmy->getPosition() - m_Owner->getPosition();
	float newdir;
	if (rand(2) == 0 && m_Owner->distanceTo(nmy) < 0.05f) // try dodging
		newdir = (float)(atan2f(n.m_y, -n.m_x) + (2 * rand(2) - 1) * 0.55f * M_PIf);
	else
		newdir = (float)(atan2f(n.m_y, -n.m_x) + randf() * 0.25f * M_PIf);
	Vector2d escape(cosf(newdir), -sinf(newdir)); // run away!
	escape.normalize();
	Vector2d separation = m_Owner->getCohesionSteer(0.2f, 0.3f * M_PIf); // avoid other agents, too
	separation.normalize();
	Vector2d borders = m_Owner->getBordersSteer(4); // avoid getting near world borders

	escape.scale(40000.0);
	separation.scale(-0.0f);
	borders.scale(10.0f);

	Vector2d dir = separation + escape + borders;
	//dir.stretchTo(1000.0);
	m_Owner->setSteer(dir);

	m_dirTick = g_game->m_time->tickNow() + minTick;
}
