#include "GameStatesManager.h"

///////////////////////////////////////////////////////////////////
#include "PlayState.h"


vector<CGameState*> CGameStatesManager::states;
bool CGameStatesManager::m_running;
//bool CGameStatesManager::m_fullscreen;
//DemoApp CGameStatesManager::myApplication;

bool CGameStatesManager::Init(const char* title, int width, int height,
	int bpp, bool fullscreen)
{
	int flags = 0;
	height;
	// initialize SDL
	//	SDL_Init(SDL_INIT_VIDEO);

	// set the title bar text
	//	SDL_WM_SetCaption(title, title);

	//	if ( fullscreen ) {
	//		flags = SDL_FULLSCREEN;
	//	}

	// create the screen surface
	//screen = SDL_SetVideoMode(width, height, bpp, flags);

//	m_fullscreen = fullscreen;
	m_running = true;

	printf("CGameStatesManager Init\n");

	// load the intro
	ChangeState(CPlayState::Instance());


	return true;


	return false;
}




void CGameStatesManager::Cleanup()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	//	if ( m_fullscreen ) {
	//	screen = SDL_SetVideoMode(640, 480, 0, 0);
	//}

	printf("CGameStatesManager Cleanup\n");

	// shutdown SDL
	//SDL_Quit();
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

void CGameStatesManager::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	// let the state draw the screen
	if (states.size() > 0)
		states.back()->Draw(renderTarget);
}

void CGameStatesManager::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	if (states.size() > 0 && !states.back()->resourcesCreated)
		states.back()->CreateDeviceResources(renderTarget);

}
