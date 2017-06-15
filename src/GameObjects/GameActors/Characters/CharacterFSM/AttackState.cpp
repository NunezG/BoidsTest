
#include "GameObjects\GameActors\Characters\CharacterFSM\AttackState.h"

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
	CAgent *nmy = m_Owner->getEnemy();

//	assert(nmy != NULL);
	nmy->m_marked = true;
//	if (!nmy->m_active || !m_Owner->canSee(nmy))  // target got away
//		return false;

	Vector2d desiredVel = nmy->getPosition() - m_Owner->getPosition();
	//intercept
	/*
	if (m_owner->getSpeed() > 0.001f) {
	float timeTaken = desiredVel.length() / m_owner->getSpeed();
	desiredVel = desiredVel + nmy->getVelocity() * timeTaken;
	}
	*/
	Vector2d steer = desiredVel;
	steer.stretchTo(10000.0f);
	m_Owner->setSteer(steer);
}
