
#include <stdio.h>

#include "gameManager.h"
#include "gamestate.h"


///////////////////////////////////////////////////////////////////

vector<CGameState*> GameManager::states;
bool GameManager::m_running;
bool GameManager::m_fullscreen;

void GameManager::Init(const char* title, int width, int height, 
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

	m_fullscreen = fullscreen;
	m_running = true;

	printf("GameManager Init\n");
}

void GameManager::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
//	if ( m_fullscreen ) {
	//	screen = SDL_SetVideoMode(640, 480, 0, 0);
	//}

	printf("GameManager Cleanup\n");

	// shutdown SDL
	//SDL_Quit();
}

void GameManager::ChangeState(CGameState* state) 
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameManager::PushState(CGameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameManager::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void GameManager::HandleEvents(UINT message)
{
	// let the state handle events
	if (states.size() > 0)
	states.back()->HandleEvents(message);
}

void GameManager::Update() 
{
	// let the state update the game
	if (states.size() > 0)
	states.back()->Update();
}

void GameManager::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	// let the state draw the screen
	if (states.size() > 0)
	states.back()->Draw(renderTarget);
}

void GameManager::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	if (states.size() > 0 && !states.back()->resourcesCreated)
	states.back()->CreateDeviceResources(renderTarget);

}
