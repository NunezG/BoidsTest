#include "GameObjects\GameActors\Characters\Character.h"

#include "GameObjects\Flag.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\FlagSeekState.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\Brain.h"
#include "GameWorld.h"





CCharacter::CCharacter(CFlagStand* TeamStand, CFlag* enemyFlag) :
	CAgent(TeamStand->initialPosition, TeamStand->GetTeam()),
	m_pFlagStand(TeamStand)
	, brain(CBrain())
	, m_TargetFlag(enemyFlag)
{
	m_sight = 0.2f;
	m_walkSpeed = 0.15f;
	setMaxSpeed(10000.0f);
};

void CCharacter::ChangeState(CStateBase* state)
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CCharacter::PushState(CStateBase* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CCharacter::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}


void CCharacter::Update()
{
	if (!m_bAlive)
	{
		if (m_bAlive) return;

		respawnTimer--;

		if (respawnTimer <= 0)
			Spawn();
	}
	else
	{
		CStateBase* currentStateFunction = getCurrentState();

		if (currentStateFunction != nullptr) {
			currentStateFunction->Update();
		}


	}
	//framesLeft_--;

	//m_fCurrentLocation.X += m_fVelocity->X;
	//m_fCurrentLocation.Y += m_fVelocity->Y;

	// Update the brain. It will run the current state function.
	brain.update();


	// Update the steering behaviors
//	boid.update();
}

CStateBase* CCharacter::getCurrentState()
{
	return states.size() > 0 ? states[states.size() - 1] : nullptr;
}

void CCharacter::Spawn()
{




	respawnTimer = 0;


	//Vector2d posDiff = Vector2d(m_pFlagStand->GetLocation().X + randomX, m_pFlagStand->GetLocation().Y + randomY); // m / s * s = m
//	m_position = m_position + posDiff; // m + m

	initialize(m_pFlagStand->initialPosition);

	//Init(m_pFlagStand->GetLocation().X + randomX, m_pFlagStand->GetLocation().Y + randomY);
	m_bAlive = true;

	CFlagSeekState* state = new CFlagSeekState(this, m_TargetFlag);

	PushState(state);

}


void CCharacter::Die()
{
	//LooseFlag();
	m_bAlive = false;
	respawnTimer = RESPAWN_SECONDS;
}