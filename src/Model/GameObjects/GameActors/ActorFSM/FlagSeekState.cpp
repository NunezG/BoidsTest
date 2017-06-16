#include "Model\GameObjects\GameActors\ActorFSM\FlagSeekState.h"
#include "Model\GameObjects\GameActors\ActorFSM\AttackState.h"
#include "Model\GameObjects\GameActors\ActorFSM\FlagReturnState.h"

#include "Model\GameObjects\GameActors\ActorFSM\EscapeState.h"
#include <iostream>
#include <string>
#include <sstream>

#include "Model\game.h"


void CFlagSeekState::Init()
{
	
	printf("CFlagSeekState Init\n");

}

void CFlagSeekState::Cleanup()
{

	printf("CFlagSeekState Cleanup\n");

}

void CFlagSeekState::Pause()
{
	printf("CFlagSeekState Pause\n");
}

void CFlagSeekState::Resume()
{
	printf("CFlagSeekState Resume\n");
}

void CFlagSeekState::Update()
{

	bool enemysurrounding = false;

	int friendsSurrounding = 0;

	CAgent* _agent = m_Owner->findNearestVisibleEnemy();

	if (_agent && m_Owner->canAttack(_agent)) //&& _agent->canDie())
	{
		m_Owner->setEnemy(_agent);
		CAttackState* state = new CAttackState(m_Owner, _agent);
		m_Owner->m_brain->PushState(state);
		return;

	}
	
	Vector2d avoidance = Vector2d(0,0);

	if (m_Owner->enemiesSurrounding() >= m_Owner->m_enemiesToDie)
	{

		avoidance = m_Owner->Avoid(m_Owner->findNearestVisibleEnemy()->getPosition());
	}
	
	Vector2d target;

	if (m_pTargetFlag->getOwner())
	{
		if (m_pTargetFlag->getOwner() && m_pTargetFlag->getOwner()->GetTeam() == m_Owner->GetTeam())
		{

			CFlagReturnState* state = new CFlagReturnState(m_Owner, m_pTargetFlag, m_homeStand);
			m_Owner->m_brain->PushState(state);
			return;
		}
		else {

			target = m_pTargetFlag->getOwner()->getPosition();

		}


		Vector2d seek = m_Owner->Seek(target);

		Vector2d dir = avoidance + seek;// +  borders
		m_Owner->setSteer(dir);
	}

}


