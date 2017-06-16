#include "Model\GameActors\ActorFSM\FlagSeekState.h"
#include "Model\GameActors\ActorFSM\AttackState.h"
#include "Model\GameActors\ActorFSM\FlagReturnState.h"

#include "Model\GameActors\ActorFSM\EscapeState.h"
#include "Model\game.h"


void CFlagSeekState::Init()
{
	

}

void CFlagSeekState::Cleanup()
{


}

void CFlagSeekState::Pause()
{
}

void CFlagSeekState::Resume()
{
}

void CFlagSeekState::Update()
{
	CAgent* _agent = m_Owner->findNearestVisibleEnemy();

	//Can attack nearest enemy
	if (_agent && m_Owner->canAttack(_agent)) //&& _agent->canDie())
	{
		m_Owner->setEnemy(_agent);
		CAttackState* state = new CAttackState(m_Owner, _agent);
		m_Owner->m_brain->PushState(state);
		return;

	}
	
	Vector2d avoidance = Vector2d(0,0);

	//Detects too much enemies
	if (m_Owner->enemiesSurrounding() >= m_Owner->m_enemiesToDie)
		avoidance = m_Owner->Avoid(_agent->getPosition());
	
	Vector2d target;

	if (m_pTargetFlag->getOwner())
	{
		if (m_pTargetFlag->getOwner()->GetTeam() == m_Owner->GetTeam())
		{
			//returnsthe flag to team stand
			CFlagReturnState* state = new CFlagReturnState(m_Owner, m_pTargetFlag, m_homeStand);
			m_Owner->m_brain->PushState(state);
			return;
		}
		else
			target = m_pTargetFlag->getOwner()->getPosition();

		Vector2d seek = m_Owner->Seek(target);

		Vector2d dir = avoidance + seek;// +  borders
		m_Owner->setSteer(dir);
	}

}


