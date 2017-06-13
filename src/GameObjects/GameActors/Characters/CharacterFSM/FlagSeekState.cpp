#include "GameObjects\GameActors\Characters\CharacterFSM\FlagSeekState.h"
#include "GameObjects/GameActors/GameObject.h"



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
	

	if (m_pTargetFlag->getOwner())
	{		

		Vector2d separation = m_Owner->getSeparationSteer(0.1f, 0.6f * M_PIf);
		//separation.normalize();
		Vector2d cohesion = m_Owner->getCohesionSteer(0.1f, 0.6f * M_PIf);
		cohesion.normalize();
		Vector2d alignment = m_Owner->getAlignmentSteer(0.1f, 0.5f * M_PIf);
		alignment.normalize();
		//        Vector2d food = m_owner->getFoodSteer(0.2f);
		//      food.normalize();

		Vector2d borders = m_Owner->getBordersSteer(2);
		//        borders.normalize();

		separation.scale(0.02f);
		cohesion.scale(2.0f);
		alignment.scale(1.3f);
		//      food.scale(1.3f);
		borders.scale(0.5f);








		Vector2d poisiton = ((CAgent*)m_Owner)->getPosition();

		Vector2d flagSeek = m_pTargetFlag->getOwner()->initialPosition - m_Owner->getPosition();
		flagSeek.normalize();
	//	m_Owner->initialPosition;
		//float deltaX =  m_pTargetFlag->getOwner()->initialPosition.m_x - m_Owner->getPosX();
		//float deltaY = m_pTargetFlag->getOwner()->initialPosition.m_y - m_Owner->getPosY();

		//CD2DHelper::ShowNum(poisiton.m_y, 3);


	//	m_Owner->getPosition().normalize();
		//m_Owner->distanceTo(m_pTargetFlag->getOwner());

		//Vector2d vec = Vector2d(deltaX, deltaY);
		//vec.normalize();


		Vector2d dir = separation + alignment + cohesion  + borders;
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
