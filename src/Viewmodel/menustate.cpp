
#include "Viewmodel\menustate.h"

CPauseState CPauseState::m_MenuState;

void CPauseState::Init()
{
	resourcesCreated = false;

//	SDL_Surface* temp = SDL_LoadBMP("menu.bmp");

//	bg = SDL_DisplayFormat(temp);

//	SDL_FreeSurface(temp);

	printf("CPauseState Init\n");
}

void CPauseState::Cleanup()
{
//	SDL_FreeSurface(bg);

	printf("CPauseState Cleanup\n");
}

void CPauseState::Pause()
{
	printf("CPauseState Pause\n");
}

void CPauseState::Resume()
{
	printf("CPauseState Resume\n");
}

void CPauseState::HandleEvents(UINT message)
{

	switch (message)
	{
	case WM_KEYDOWN:
		CGameStatesManager::PopState();
		break;


	}

//	SDL_Event event;

//	if (SDL_PollEvent(&event)) {
	//	switch (event.type) {
	//		case SDL_QUIT:
	//			game->Quit();
	//			break;

	//		case SDL_KEYDOWN:
//				switch (event.key.keysym.sym) {
	//				case SDLK_ESCAPE:
//						game->PopState();
//						break;
//				}
//				break;
//		}
//	}
}

void CPauseState::Update() 
{

}

void CPauseState::Draw(ID2D1HwndRenderTarget* renderTarget)
{
//	SDL_BlitSurface(bg, NULL, game->screen, NULL);
//	SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}



void CPauseState::CreateMaterials(ID2D1HwndRenderTarget* renderTarget)
{


}
