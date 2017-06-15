#include "GameObjects\GameActors\Characters\Character.h"

#include "GameObjects\Flag.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\FlagSeekState.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\Brain.h"
#include "GameWorld.h"





CCharacter::CCharacter(CFlagStand* TeamStand, CFlag* enemyFlag) :
	CGameObject(TeamStand->getPosition(), TeamStand->GetTeam())
{

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



CStateBase* CCharacter::getCurrentState() const
{
	return states.size() > 0 ? states[states.size() - 1] : nullptr;
}

