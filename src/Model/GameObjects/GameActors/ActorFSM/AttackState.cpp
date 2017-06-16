
#include "Model\GameObjects\GameActors\ActorFSM\AttackState.h"

void CAttackState::Init()
{
	
	printf("CAttackState Init\n");

}

void CAttackState::Cleanup()
{

	printf("CIdleState Cleanup\n");

}

void CAttackState::Pause()
{
	printf("CIdleState Pause\n");
}

void CAttackState::Resume()
{
	printf("CIdleState Resume\n");
}

void CAttackState::Update()
{

	CAgent *nmy = m_Owner->getEnemy();

	if (!m_Owner->canAttack(nmy) || !nmy->m_active)
	{
		m_Owner->setEnemy(nullptr);
		m_Owner->m_brain->PopState();
		return;
	}

	m_Owner->Attack(nmy->getPosition());

}
