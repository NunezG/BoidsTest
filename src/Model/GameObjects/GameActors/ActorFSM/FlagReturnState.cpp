#include "Model\GameObjects\GameActors\ActorFSM\FlagReturnState.h"
#include "Model\GameObjects\GameActors\ActorFSM\AttackState.h"

#include "Model\GameObjects\GameActors\ActorFSM\EscapeState.h"
#include <iostream>
#include <string>
#include <sstream>

#include "Model\game.h"


void CFlagReturnState::Init()
{
	
	printf("CFlagReturnState Init\n");

}

void CFlagReturnState::Cleanup()
{

	printf("CFlagReturnState Cleanup\n");

}

void CFlagReturnState::Pause()
{
	printf("CFlagReturnState Pause\n");
}

void CFlagReturnState::Resume()
{
	printf("CFlagReturnState Resume\n");
}

void CFlagReturnState::Update()
{

	bool enemysurrounding = false;

	int friendsSurrounding = 0;

	CAgent* _agent = m_Owner->findNearestVisibleEnemy();


	
	Vector2d avoidance = Vector2d(0,0);

	if (m_Owner->enemiesSurrounding() >= m_Owner->m_enemiesToDie)
	{

		avoidance = m_Owner->Avoid(m_Owner->findNearestVisibleEnemy()->getPosition());

	}



	Vector2d target;

	if (m_pTargetFlag->getOwner())
	{
		if (m_pTargetFlag->getOwner()->GetTeam() != m_Owner->GetTeam())
		{
			m_Owner->m_brain->PopState();
			return;

		}


		if (m_pTargetFlag->getOwner() == m_Owner)
		{
			//Owner is the leader
			CFlagStand* stand = m_Owner->getFlagStand();


			target = stand->getPosition();

			//Aggresive way
			Vector2d attackStand = m_Owner->Attack(target);

			attackStand.scale(500.f);

			Vector2d dir = avoidance + attackStand;// +  borders
			m_Owner->setSteer(dir);


		}
		else
		{

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

			seek.scale(500.0f);

			Vector2d dir = avoidance + seek;// +  borders
			m_Owner->setSteer(dir);


		}




	}




}


