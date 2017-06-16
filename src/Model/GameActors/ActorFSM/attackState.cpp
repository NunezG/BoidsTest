
#include "Model\GameActors\ActorFSM\attackState.h"
#include "Model\GameActors\agent.h"


void CAttackState::Init()
{
	

}

void CAttackState::Cleanup()
{


}

void CAttackState::Pause()
{
}

void CAttackState::Resume()
{
}

void CAttackState::Update()
{

	CAgent *nmy = m_Owner->getEnemy();

	if (!m_Owner->canAttack(nmy) || !nmy->m_active)
	{
		//cannot attack or already dead
		m_Owner->setEnemy(nullptr);
		m_Owner->m_brain->PopState();
		return;
	}

	m_Owner->Attack(nmy->getPosition());

}
