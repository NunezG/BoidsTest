#include "Model\GameObjects\GameActors\CharacterFSM.h"

#include "Model\GameObjects\Flag.h"
#include "Model\GameObjects\GameActors\ActorFSM\FlagSeekState.h"
//#include "GameObjects\GameActors\ActorFSM\Brain.h"


void CCharacterFSM::ChangeState(CStateBase* state)
{
	// cleanup the current state
	if (!states.empty()) {
		CStateBase* state = states.back();
		state->Cleanup();
		states.pop_back();
		delete state;

	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CCharacterFSM::PushState(CStateBase* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CCharacterFSM::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		CStateBase* state = states.back();
		state->Cleanup();
		states.pop_back();
		delete state;
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}

CStateBase* CCharacterFSM::getCurrentState() const
{
	return states.size() > 0 ? states[states.size() - 1] : nullptr;
}


void CCharacterFSM::Update()
{
	CStateBase* currentStateFunction = getCurrentState();
	if (currentStateFunction != nullptr) {
		currentStateFunction->Update();
	}
}

void CCharacterFSM::Init()
{
	for (int i = 0; i < states.size(); i++)
	{
		PopState();

	}
}