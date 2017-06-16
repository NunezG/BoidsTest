#include "ViewModel\introstate.h"
//#include "playstate.h"

CIntroState CIntroState::m_IntroState;

#include "ViewModel\PlayState.h";

void CIntroState::Init()
{
	resourcesCreated = false;

	printf("CIntroState Init\n");





}


void CIntroState::Cleanup()
{
//	SDL_FreeSurface(bg);
//	SDL_FreeSurface(fader);

	printf("CIntroState Cleanup\n");
}

void CIntroState::Pause()
{
	printf("CIntroState Pause\n");
}

void CIntroState::Resume()
{
	printf("CIntroState Resume\n");
}

void CIntroState::HandleEvents(UINT message)
{
	switch (message)
	{
		case WM_KEYDOWN:
			ChangeState(CPlayState::Instance());
			break;

		
	}
//	SDL_Event event;

//	if (SDL_PollEvent(&event)) {
//		switch (event.type) {
//			case SDL_QUIT:
//				game->Quit();
//				break;

//			case SDL_KEYDOWN:
//				switch (event.key.keysym.sym) {
//					case SDLK_SPACE:
//						game->ChangeState( CPlayState::Instance() );
//						break;

//					case SDLK_ESCAPE:
//						game->Quit();
//						break;
//				}
//				break;
//		}
//	}
}

void CIntroState::Update() 
{
	buildFrameConstant();

	if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		CD2DHelper::m_pRenderTarget->BeginDraw();

		Draw(CD2DHelper::m_pRenderTarget);

		CD2DHelper::m_pRenderTarget->EndDraw();
	}
}

void CIntroState::CreateMaterials(ID2D1HwndRenderTarget* renderTarget)
{

	resourcesCreated = true;

}


void CIntroState::Draw(ID2D1HwndRenderTarget* renderTarget)
{

	static const char sc_title[] = "LIONS VS ANTELOPES";
	static const char sc_subtitle[] = "Press any key to start";

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));


	CD2DHelper::outText(0, -300, sc_title);

	CD2DHelper::outText(0, 0, sc_subtitle);

}


