#include "ViewModel\endGameState.h"
//#include "playstate.h"

CEndGameState CEndGameState::m_EndGameState;

#include "ViewModel\PlayState.h";
#include "Model\game.h"

void CEndGameState::Init()
{
	resourcesCreated = false;
	

	printf("CEndGameState Init\n");





}


void CEndGameState::Cleanup()
{


	printf("CEndGameState Cleanup\n");
}

void CEndGameState::Pause()
{
	printf("CEndGameState Pause\n");
}

void CEndGameState::Resume()
{
	printf("CEndGameState Resume\n");
}

void CEndGameState::HandleEvents(UINT message)
{
	switch (message)
	{
		case WM_KEYDOWN:
			CGameStatesManager::PopState();
			CGameStatesManager::PopState();
			ChangeState(CPlayState::Instance());
			break;

		
	}

}

void CEndGameState::Update() 
{
	buildFrameConstant();

	if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		CD2DHelper::m_pRenderTarget->BeginDraw();

		Draw(CD2DHelper::m_pRenderTarget);

		CD2DHelper::m_pRenderTarget->EndDraw();
	}
}

void CEndGameState::CreateMaterials(ID2D1HwndRenderTarget* renderTarget)
{
	
	resourcesCreated = true;

}


void CEndGameState::Draw(ID2D1HwndRenderTarget* renderTarget)
{

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	static const char* sc_end = "GAME FINISHED";
	char* sc_winer;

	if (g_game->counter[0] >= WIN_CONDITION)
		sc_winer = "ANTELOPES WIN";
	else
		sc_winer = "LIONS WIN";


	CD2DHelper::outText(0, -300, sc_end);

	CD2DHelper::outText(0, 0, sc_winer);



}
