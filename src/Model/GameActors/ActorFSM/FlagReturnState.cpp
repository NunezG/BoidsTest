#include "Model\GameActors\ActorFSM\flagReturnState.h"
#include "Model\GameActors\ActorFSM\attackState.h"
#include "Model\GameActors\ActorFSM\escapeState.h"
#include "Model\game.h"


void CFlagReturnState::Init()
{
	
}

void CFlagReturnState::Cleanup()
{

}

void CFlagReturnState::Pause()
{
}

void CFlagReturnState::Resume()
{
}

void CFlagReturnState::Update()
{

	CAgent* _agent = m_Owner->findNearestVisibleEnemy();
	
	Vector2d avoidance = Vector2d(0,0);

	if (m_Owner->enemiesSurrounding() >= m_Owner->m_enemiesToDie)
		avoidance = m_Owner->Avoid(_agent->getPosition());

	Vector2d target;

	if (m_pTargetFlag->getOwner())
	{
		if (m_pTargetFlag->getOwner()->GetTeam() != m_Owner->GetTeam())
		{
			//Flag lost or returned
			m_Owner->m_brain->PopState();
			return;

		}


		if (m_pTargetFlag->getOwner() == m_Owner)
		{
			//Owner is the LEADER
			CFlagStand* stand = m_Owner->getFlagStand();


			target = stand->getPosition();

			//Aggresive way
			Vector2d attackStand = m_Owner->Attack(target);

			attackStand.scale(1);

			Vector2d cohesion = m_Owner->getCohesionSteer(100, 2.f * M_PIf);
			cohesion.scale(1);
			Vector2d dir = avoidance + attackStand + cohesion;
			m_Owner->setSteer(dir);


		}
		else
		{
			//FOLLOWER
			target = m_pTargetFlag->getOwner()->getPosition();


			//Only followers will attack
			if (_agent && m_Owner->canAttack(_agent)) //&& _agent->canDie())
			{
				m_Owner->setEnemy(_agent);
				CAttackState* state = new CAttackState(m_Owner, _agent);
				m_Owner->m_brain->PushState(state);
				return;

			}


			Vector2d seek = m_Owner->Seek(target);

			seek.scale(5000.0f);

			

			Vector2d dir = avoidance + seek;
			m_Owner->setSteer(dir);


		}




	}




}


