#include "ViewModel\gameStatesManager.h"

///////////////////////////////////////////////////////////////////
#include "ViewModel\PlayState.h"


vector<CGameState*> CGameStatesManager::states;
bool CGameStatesManager::m_running;

bool CGameStatesManager::Init()
{
	m_running = true;

	// load the intro
	ChangeState(CPlayState::Instance());

	return true;
}

void CGameStatesManager::Cleanup()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}
}

void CGameStatesManager::ChangeState(CGameState* state)
{

	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	CreateDeviceResources();
	states.back()->Init();
}

void CGameStatesManager::PushState(CGameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CGameStatesManager::PopState()
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


void CGameStatesManager::HandleEvents(UINT message)
{
	// let the state handle events
	if (states.size() > 0)
		states.back()->HandleEvents(message);
}

void CGameStatesManager::Update()
{
	// let the state update the game
	if (states.size() > 0)
		states.back()->Update();
}

void CGameStatesManager::Draw()
{
	// let the state draw the screen
	if (states.size() > 0)
		states.back()->Draw();
}

void CGameStatesManager::CreateDeviceResources()
{
	if (states.size() > 0 && !states.back()->resourcesCreated)
		states.back()->CreateMaterials();

}

