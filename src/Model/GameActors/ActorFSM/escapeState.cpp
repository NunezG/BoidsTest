#include "Model\GameActors\ActorFSM\escapeState.h"
#include "Model/GameActors/characterFSM.h"

void CEscapeState::Init()
{
	m_Owner->m_done = false;
}

void CEscapeState::Cleanup()
{
}

void CEscapeState::Pause()
{
}

void CEscapeState::Resume()
{
}

void CEscapeState::Update()
{
	if (m_Owner->enemiesSurrounding() < m_Owner->m_enemiesToDie)
	{
		//No enemies on sight
		m_Owner->m_brain->PopState();

		return;
	}

	CAgent *nmy = m_Owner->getEnemy();

	m_Owner->Avoid(nmy->getPosition());
	
}
