
#include "GameObjects\GameActors\Characters\CharacterFSM\AttackState.h"

CAttackState CAttackState::m_IdleState;

void CAttackState::Init()
{
	


}

void CAttackState::Cleanup()
{
//	SDL_FreeSurface(bg);
//	SDL_FreeSurface(fader);

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
	
}
