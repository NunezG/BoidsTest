
#include "Viewmodel\menustate.h"

CPauseState CPauseState::m_MenuState;

void CPauseState::Init()
{
	resourcesCreated = false;
}

void CPauseState::Cleanup()
{

}

void CPauseState::Pause()
{
}

void CPauseState::Resume()
{
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

	if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		CD2DHelper::m_pRenderTarget->BeginDraw();

		Draw();

		CD2DHelper::m_pRenderTarget->EndDraw();
	}
}

void CPauseState::Draw()
{
	static const char sc_pause[] = "PAUSE";

	CD2DHelper::m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	CD2DHelper::outText(0, -300, sc_pause);

}



void CPauseState::CreateMaterials()
{
	resourcesCreated = true;


}
