
#include "GameObjects\GameActors\Characters\CharacterFSM\AttackState.h"

void CAttackState::Init(CCharacter* owner)
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
