
//#include <stdio.h>

#include "ObjectManager.h"
//#include "../FSM/Game/gamestate.h"


///////////////////////////////////////////////////////////////////

//vector<CGameState*> CObjectManager::states;
//bool CObjectManager::m_running;
bool CObjectManager::m_fullscreen;

void CObjectManager::Init(const char* title, int width, int height, 
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
	//m_running = true;

	printf("CObjectManager Init\n");
}

void CObjectManager::Cleanup()
{
	// cleanup the all states
/*	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
*/
	// switch back to windowed mode so other 
	// programs won't get accidentally resized
//	if ( m_fullscreen ) {
	//	screen = SDL_SetVideoMode(640, 480, 0, 0);
	//}

	printf("CObjectManager Cleanup\n");

	// shutdown SDL
	//SDL_Quit();
}
/*

void CObjectManager::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	// let the state draw the screen
	if (states.size() > 0)
	states.back()->Draw(renderTarget);
}

void CObjectManager::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	if (states.size() > 0 && !states.back()->resourcesCreated)
	states.back()->CreateDeviceResources(renderTarget);

}
*/