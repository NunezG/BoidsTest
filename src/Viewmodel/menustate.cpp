
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
}

void CPauseState::Update() 
{
	buildFrameConstant();
	//renderFrame();

	if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		CD2DHelper::m_pRenderTarget->BeginDraw();

		Draw(CD2DHelper::m_pRenderTarget);

		//CD2DHelper::DebugFrame();

		CD2DHelper::m_pRenderTarget->EndDraw();
	}
}

void CPauseState::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	static const char sc_pause[] = "PAUSE";

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

//	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	CD2DHelper::outText(0, -300, sc_pause);

}



void CPauseState::CreateMaterials(ID2D1HwndRenderTarget* renderTarget)
{
	resourcesCreated = true;


}
