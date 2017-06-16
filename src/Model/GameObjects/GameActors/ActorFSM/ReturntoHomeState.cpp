#include "Model\GameObjects\GameActors\ActorFSM\ReturnToHomeState.h"
#include "Model\GameObjects\GameActors\ActorFSM\AttackState.h"

#include "Model\GameObjects\GameActors\ActorFSM\EscapeState.h"
#include <iostream>
#include <string>
#include <sstream>


//#include "GameObjects\GameActors\agent.h"
#include "Model\game.h"


void CReturnToHomeState::Init()
{
	
	printf("CReturnToHomeState Init\n");

}

void CReturnToHomeState::Cleanup()
{
//	SDL_FreeSurface(bg);
//	SDL_FreeSurface(fader);

	printf("CReturnToHomeState Cleanup\n");
}

void CReturnToHomeState::Pause()
{
	//printf("CReturnToHomeState Pause\n");
}

void CReturnToHomeState::Resume()
{
	printf("CReturnToHomeState Resume\n");
}

void CReturnToHomeState::Update()
{

	bool enemysurrounding = false;

	int friendsSurrounding = 0;

	CAgent* nearEnemy;

	for (std::list <CAgent*>::iterator agent = g_game->m_agents.begin(); agent != g_game->m_agents.end(); agent++) {
		CAgent* _agent = static_cast<CAgent*>((*agent));

		if (_agent->m_active)
		{

			float distance = (m_Owner->getPosition() - _agent->getPosition()).length();

		//	float deltaX = (((CGameObject*)m_Owner)->getPosX() - _agent.getPosX());
		//	float deltaY = (((CGameObject*)m_Owner)->getPosY() - _agent.getPosY());


			//double distance = sqrt((deltaX * deltaX) - (deltaY * deltaY));
			Vector2d position = _agent->getPosition();

/*
			std::cout << "(OWNERRR  " << distance << std::endl;
			std::cout << "2  " << (int)((CGameObject*)m_Owner)->getPosition().m_x << std::endl;
			std::cout << "3  " << (int)((CAgent*)m_Owner)->getPosition().m_x << std::endl;
			std::cout << "4  " << (int)m_Owner->getPosition().m_x << std::endl;

			// m_minDirTick = 2000.0f;
			std::cout << "(ENEMY SURROUNDING  " << distance << std::endl;
			std::cout << "2  " << (int)((CGameObject&)_agent).getPosition().m_x << std::endl;
			std::cout << "3  " << (int)((CAgent&)_agent).getPosition().m_x << std::endl;
			std::cout << "4  " << (int)_agent->getPosX() << std::endl;
			std::cout << "5  " << (int)position.m_x << std::endl;
			*/
			if (_agent->GetTeam() == m_Owner->GetTeam())
			{
	

				if (distance < 20) {
				//	printf("C AGENT SURROUNDING\n");

					friendsSurrounding++;
					//newDirection(m_minDirTick);
				//	return;

				}
			}
			else
			{



				if (distance < 20) {
					

					
					printf("C ENEMY SURROUNDING\n");

					enemysurrounding = true;
					nearEnemy = _agent;
					m_Owner->setEnemy(_agent);
					CEscapeState* state = new CEscapeState(m_Owner);
					m_Owner->m_brain->PushState(state);

					//	newDirection(m_minDirTick);
					return;
				}

			}
		}



	}



	Vector2d objecive;

	if (m_pTargetFlag->getOwner())
	{
		if (m_pTargetFlag->getOwner() && m_pTargetFlag->getOwner()->GetTeam() == m_Owner->GetTeam())
		{

			//TEAM HAS FLAG
			CFlagStand* stand = m_Owner->getFlagStand();

			objecive = g_game->stands[0].getPosition();
				//((CGameObject*)m_homeStand)->getPosition();


		}
		else {
			//
			if ((m_pTargetFlag->getOwner())->IsOfTeam(m_Owner->GetTeam()))
			{
				//flag lost

				//m_pTargetFlag->getOwner()->LooseFlag();
				//m_pTargetFlag->setOwner(m_Owner);
			//	((CGameObject*)m_Owner)->ReceiveFlag(m_pTargetFlag);


			}

			// objecive = m_pTargetFlag->getOwner()->getPosition();

		}



		Vector2d separation = m_Owner->getSeparationSteer(20.f, 2.f * M_PIf);
		//separation.normalize();
		Vector2d cohesion = m_Owner->getCohesionSteer(60, 2.f * M_PIf);
		cohesion.normalize();
		Vector2d alignment = m_Owner->getAlignmentSteer(20.f, 2.f * M_PIf);
		alignment.normalize();
		//        Vector2d food = m_owner->getFoodSteer(0.2f);
		//      food.normalize();

		Vector2d borders = m_Owner->getBordersSteer(1);
		//        borders.normalize();

		separation.scale(350.f);
		cohesion.scale(10.0f);
		alignment.scale(10.3f);
		//      food.scale(1.3f);
		borders.scale(0.01f);

		Vector2d delta = objecive - ((CGameObject*)m_Owner)->getPosition();


		//delta.normalize();
		delta.scale(0.1f);
		//	m_Owner->initialPosition;
		//float deltaX =  m_pTargetFlag->getOwner()->initialPosition.m_x - m_Owner->getPosX();
		//float deltaY = m_pTargetFlag->getOwner()->initialPosition.m_y - m_Owner->getPosY();

		//CD2DHelper::ShowNum(poisiton.m_y, 3);


		//	m_Owner->getPosition().normalize();
		//m_Owner->distanceTo(m_pTargetFlag->getOwner());

		//Vector2d vec = Vector2d(deltaX, deltaY);
		//vec.normalize();


		Vector2d dir = separation + cohesion + alignment + delta;
		m_Owner->setSteer(dir);

		//	m_Owner->setSteer(flagSeek *1000);
		//m_Owner->move();

		//	CD2DHelper::ShowNum(((CAgent*)m_Owner)->getPosition().m_x, 3);

		// Move the ant towards the leaf.
		//velocity = D2D1::Point2F();
		/*		new Vector3D(Game.instance.leaf.x - position.x, Game.instance.leaf.y - position.y);

		if (distance(Game.instance.leaf, this) <= 10) {
		// The ant is extremelly close to the leaf, it's time
		// to go home.
		brain.popState(); // removes "findLeaf" from the stack.
		brain.pushState(goHome); // push "goHome" state, making it the active state.
		}

		if (distance(Game.mouse, this) <= MOUSE_THREAT_RADIUS) {
		// Mouse cursor is threatening us. Let's run away!
		// The "runAway" state is pushed on top of "findLeaf", which means
		// the "findLeaf" state will be active again when "runAway" ends.
		brain.pushState(runAway);
		}
		*/
	}



	
}

