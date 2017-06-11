
//#include <stdio.h>

#include "GameWorld.h"
//#include "FSM\Game\gamestate.h"


///////////////////////////////////////////////////////////////////

//vector<CGameState*> CGameWorld::states;
bool CGameWorld::m_running;
//CObjectManager* CGameWorld::m_objectManager;

//bool CGameWorld::m_fullscreen;

bool CGameWorld::Init(const char* title, int width, int height, 
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

	//m_fullscreen = fullscreen;
	m_running = true;

	printf("CGameWorld Init\n");

	return true;
}

void CGameWorld::Cleanup()
{

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
//	if ( m_fullscreen ) {
	//	screen = SDL_SetVideoMode(640, 480, 0, 0);
	//}

	printf("CGameWorld Cleanup\n");

	// shutdown SDL
	//SDL_Quit();
}



void CGameWorld::HandleEvents(UINT message)
{
	
}

void CGameWorld::Update() 
{

}

void CGameWorld::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	
}

void CGameWorld::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	

}
