#include "GameObjects\GameActors\Characters\CharacterFSM\FlagSeekState.h"
#include "GameObjects/GameActors/Characters/Character.h"



void CFlagSeekState::Init()
{


}

void CFlagSeekState::Cleanup()
{
	//	SDL_FreeSurface(bg);
	//	SDL_FreeSurface(fader);

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

	Vector2d objecive;



	if (m_pTargetFlag->getOwner())
	{

		if ((CCharacter*)m_pTargetFlag->getOwner() && m_pTargetFlag->getOwner()->GetTeam() == ((CTeamObject*)m_Owner)->GetTeam())
		{
			//TEAM HAS FLAG
			objecive = m_Owner->getFlagStand()->getPosition();


		}
		else {

			if ((((CGameObject*)m_pTargetFlag->getOwner())->getPosition() - ((CGameObject*)m_Owner)->getPosition()).length() < 10)
			{
				m_pTargetFlag->getOwner()->LooseFlag();
				m_pTargetFlag->setOwner((CGameObject*)m_Owner);
				((CGameObject*)m_Owner)->ReceiveFlag(m_pTargetFlag);


			}

			Vector2d poisiton = ((CGameObject*)m_Owner)->getPosition();
			objecive = ((CGameObject*)m_pTargetFlag->getOwner())->getPosition() - poisiton;

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



		objecive.normalize();
		objecive.scale(50.f);
	//	m_Owner->initialPosition;
		//float deltaX =  m_pTargetFlag->getOwner()->initialPosition.m_x - m_Owner->getPosX();
		//float deltaY = m_pTargetFlag->getOwner()->initialPosition.m_y - m_Owner->getPosY();

		//CD2DHelper::ShowNum(poisiton.m_y, 3);


	//	m_Owner->getPosition().normalize();
		//m_Owner->distanceTo(m_pTargetFlag->getOwner());

		//Vector2d vec = Vector2d(deltaX, deltaY);
		//vec.normalize();


		Vector2d dir = separation + cohesion + alignment + objecive;
		m_Owner->setSteer(dir);

	//	m_Owner->setSteer(flagSeek *1000);
		m_Owner->move();

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
