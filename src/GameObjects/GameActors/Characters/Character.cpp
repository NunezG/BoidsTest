#include "GameObjects\GameActors\Characters\Character.h"

#include "GameObjects\Flag.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\FlagSeekState.h"
#include "GameObjects\GameActors\Characters\Boid.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\Brain.h"
#include "GameWorld.h"





CCharacter::CCharacter(CFlagStand* TeamStand, CFlag* enemyFlag) :
	m_pFlagStand(TeamStand)
	, CGameObject(TeamStand->GetLocation()
	, TeamStand->GetTeam())
	, brain(CBrain())
	, boid(CBoid())
{
	m_TargetFlag = enemyFlag;

	CFlagSeekState* state =  new CFlagSeekState(this, m_TargetFlag);
	PushState(state);


};

void CCharacter::ChangeState(CCharacterState* state)
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

void CCharacter::PushState(CCharacterState* state)
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
	boid.update();
}

CStateBase* CCharacter::getCurrentState()
{
	return states.size() > 0 ? states[states.size() - 1] : nullptr;
}

void CCharacter::Spawn()
{

	float randomX = (float)(rand() % (RANDOM_SPAWN * 2 + 1) - RANDOM_SPAWN);
	float randomY = (float)(rand() % (RANDOM_SPAWN * 2 + 1) - RANDOM_SPAWN);

	respawnTimer = 0;
	
	m_fCurrentLocation.X = m_pFlagStand->GetLocation().X + randomX;
	m_fCurrentLocation.Y = m_pFlagStand->GetLocation().Y + randomY;

	//Init(m_pFlagStand->GetLocation().X + randomX, m_pFlagStand->GetLocation().Y + randomY);
	m_bAlive = true;

}


void CCharacter::Die()
{
	LooseFlag();
	m_bAlive = false;
	respawnTimer = RESPAWN_SECONDS;
}