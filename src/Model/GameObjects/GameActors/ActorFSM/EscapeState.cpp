#include "Model\GameObjects\GameActors\ActorFSM\EscapeState.h"
#include "Model\GameObjects/GameActors/CharacterFSM.h"



void CEscapeState::Init()
{
	printf("CEscapeState InitT\n");

	m_Owner->m_done = false;

}

void CEscapeState::Cleanup()
{

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
	if (m_Owner->enemiesSurrounding() < m_Owner->m_enemiesToDie)
	{
		m_Owner->m_brain->PopState();

		return;
	}


	CAgent *nmy = m_Owner->getEnemy();


	m_Owner->Avoid(nmy->getPosition());


	
}
