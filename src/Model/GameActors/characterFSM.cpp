#include "Model\GameActors\CharacterFSM.h"
#include "Model\GameActors\ActorFSM\FlagSeekState.h"

void CCharacterFSM::ChangeState(CStateBase* state)
{
	// cleanup the current state
	if (!states.empty()) {
		CStateBase* oldState = states.back();
		oldState->Cleanup();
		states.pop_back();
		delete oldState;

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
	for (unsigned int i = 0; i < states.size(); i++)
	{
		PopState();

	}
}


void CCharacterFSM::Cleanup()
{
	// cleanup all states
	while (!states.empty()) {
		CStateBase* state = states.back();
		state->Cleanup();
		states.pop_back();
		delete state;
	}
}