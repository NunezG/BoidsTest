

#include "IdleState.h"

CIdleState CIdleState::m_IdleState;

void CIdleState::Init()
{
	


}

void CIdleState::Cleanup()
{
//	SDL_FreeSurface(bg);
//	SDL_FreeSurface(fader);

	printf("CIdleState Cleanup\n");
}

void CIdleState::Pause()
{
	printf("CIdleState Pause\n");
}

void CIdleState::Resume()
{
	printf("CIdleState Resume\n");
}

void CIdleState::Update() 
{
	
}
