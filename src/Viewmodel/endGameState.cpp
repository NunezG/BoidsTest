#include "ViewModel\endGameState.h"
#include "ViewModel\PlayState.h"
#include "Model\game.h"

CEndGameState CEndGameState::m_EndGameState;

void CEndGameState::Init()
{
	resourcesCreated = false;
}

void CEndGameState::Cleanup()
{
}

void CEndGameState::Pause()
{
}

void CEndGameState::Resume()
{
}

void CEndGameState::HandleEvents(UINT message)
{
	switch (message)
	{
		case WM_KEYDOWN:
			CGameStatesManager::PopState();
			CGameStatesManager::PopState();
			CGameStatesManager::ChangeState(CPlayState::Instance());
			break;	
	}

}

void CEndGameState::Update() 
{
	buildFrameConstant();

	if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		CD2DHelper::m_pRenderTarget->BeginDraw();

		Draw();

		CD2DHelper::m_pRenderTarget->EndDraw();
	}
}

void CEndGameState::CreateMaterials()
{
	
	resourcesCreated = true;

}


void CEndGameState::Draw()
{
	CD2DHelper::m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	CD2DHelper::m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	static const char* sc_end = "GAME FINISHED";
	char* sc_winer;

	if (g_game->counter[0] >= WIN_CONDITION)
		sc_winer = "ANTELOPES WIN";
	else
		sc_winer = "LIONS WIN";


	CD2DHelper::outText(0, -300, sc_end);

	CD2DHelper::outText(0, 0, sc_winer);



}
