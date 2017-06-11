#include "GameObjects\GameActors\Characters\CharacterFSM\FlagSeekState.h"

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

		//m_pTargetFlag->getOwner()
		

		float deltaX = m_pTargetFlag->getOwner()->GetLocation().X - m_Owner->GetLocation().X;
		float deltaY = m_pTargetFlag->getOwner()->GetLocation().Y - m_Owner->GetLocation().Y;


		m_Owner->SetLocation((float)(m_Owner->GetLocation().X + deltaX / 100.0f), m_Owner->GetLocation().Y + deltaY / 100);

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
