#include "GameObjects\GameActors\Characters\CharacterFSM\EscapeState.h"
#include "GameObjects/GameActors/Characters/Character.h"



void CEscapeState::Init()
{
	printf("CEscapeState InitTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");

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
	CAgent *nmy = m_Owner->getEnemy();
//	assert(nmy != NULL);
	
		if (g_game->m_time->tickNow() > m_dirTick) {
			if (nmy->m_active && m_Owner->canSee(nmy))
				newDirection(m_minDirTick);
			else {
				newDirection(5 * m_minDirTick); // keep running for a while, just in case
				m_Owner->m_done = true;
			}
		}
	



	
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
