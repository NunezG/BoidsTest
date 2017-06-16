#include "ViewModel\introstate.h"
#include "ViewModel\PlayState.h"

CIntroState CIntroState::m_IntroState;


void CIntroState::Init()
{
	resourcesCreated = false;
}


void CIntroState::Cleanup()
{
}

void CIntroState::Pause()
{
}

void CIntroState::Resume()
{
}

void CIntroState::HandleEvents(UINT message)
{
	switch (message)
	{
		case WM_KEYDOWN:
			CGameStatesManager:: ChangeState(CPlayState::Instance());
			break;	
	}

}

void CIntroState::Update() 
{
	buildFrameConstant();

	if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		CD2DHelper::m_pRenderTarget->BeginDraw();

		Draw();

		CD2DHelper::m_pRenderTarget->EndDraw();
	}
}

void CIntroState::CreateMaterials()
{

	resourcesCreated = true;

}

void CIntroState::Draw()
{

	static const char sc_title[] = "LIONS VS ANTELOPES";
	static const char sc_subtitle[] = "Press any key to start";

	CD2DHelper::m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	CD2DHelper::m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));


	CD2DHelper::outText(0, -300, sc_title);

	CD2DHelper::outText(0, 0, sc_subtitle);

}


