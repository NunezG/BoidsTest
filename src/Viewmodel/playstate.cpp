

#include "Viewmodel\playstate.h"
#include "Viewmodel\menustate.h"
#include "Viewmodel\endGameState.h"
#include <cmath>
#include "Model\game.h"
#include "Model\GameActors\agent.h"



CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
	g_game = new CGame(LIONS_NUMBER, ANTELOPES_NUMBER);

	g_game->m_time->reset();

	g_game->m_time->setSpeed(s_speed);

	resourcesCreated = false;

}

void CPlayState::Cleanup()
{
}

void CPlayState::Pause()
{
	g_game->m_time->setSpeed(0);

}

void CPlayState::Resume()
{
	g_game->m_time->setSpeed(s_speed);
}

void CPlayState::HandleEvents(UINT message)
{

	switch (message)
	{
	case WM_KEYDOWN:
		CGameStatesManager::PushState(CPauseState::Instance());
		break;


	}
}

void CPlayState::Update()
{
	
	TRealTime now = g_game->m_time->timeNow();

	g_game->Tick();




	if (g_game->gammeFinished)
		CGameStatesManager::ChangeState(CEndGameState::Instance());


	if (g_game->getDesiredFramesDone(now, s_fps) >g_game-> getRenderedSinceSecond()) {

		g_game->newFrame();
		buildFrameConstant();

		if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			CD2DHelper::m_pRenderTarget->BeginDraw();

			Draw();

			CD2DHelper::DebugFrame();

			CD2DHelper::m_pRenderTarget->EndDraw();
		}

	}

}

void CPlayState::Draw()
{

	CD2DHelper::m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	CD2DHelper::m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F rtSize = CD2DHelper::m_pRenderTarget->GetSize();

	// Draw a grid background.
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);

	for (int x = 0; x < width; x += 10)
	{
		CD2DHelper::m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			m_pLightSlateGrayBrush,
			0.5f
		);
	}

	for (int y = 0; y < height; y += 10)
	{
		CD2DHelper::m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			m_pLightSlateGrayBrush,
			0.5f
		);
	}

	for (std::list <CAgent *>::iterator _agent = g_game->m_agents.begin(); _agent != g_game->m_agents.end(); _agent++) {
		CAgent *agent = (*_agent);
		if (agent->m_active) {

			Vector2d poisiton = agent->getPosition();
			ID2D1SolidColorBrush*	characterColor;


			if (agent->GetTeam() == antelopesTeam)
				characterColor = m_pAntelopeTeamColor;
			else
				characterColor = m_pLionTeamColor;

			CD2DHelper::Rectange(200, characterColor, poisiton.m_x, poisiton.m_y, std::atan2(agent->getVelocity().m_x, agent->getVelocity().m_y));
		
		}
	}

	CD2DHelper::Rectange(40, m_pAntelopeTeamColor, g_game->stands[0].getPosX(), g_game->stands[0].getPosY());
	CD2DHelper::Rectange(40, m_pLionTeamColor, g_game->stands[1].getPosX(), g_game->stands[1].getPosY());


	if (g_game->m_pFlags[0])
		CD2DHelper::Rectange(200, m_pAntelopeFlagColor, g_game->m_pFlags[0]->getOwner()->getPosX(), g_game->m_pFlags[0]->getOwner()->getPosY());

	if (g_game->m_pFlags[1])
		CD2DHelper::Rectange(200, m_pLionFlagColor, g_game->m_pFlags[1]->getOwner()->getPosX(), g_game->m_pFlags[1]->getOwner()->getPosY());

}


void CPlayState::CreateMaterials()
{
	HRESULT hr = S_OK;


	// Create a gray brush.

	hr = CD2DHelper::m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Gray),

		&m_pLightSlateGrayBrush

	);

	hr = CD2DHelper::m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::YellowGreen),

		&m_pLionTeamColor

	);

	hr = CD2DHelper::m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Maroon),

		&m_pAntelopeTeamColor

	);

	hr = CD2DHelper::m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Yellow),

		&m_pLionFlagColor

	);


	hr = CD2DHelper::m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Red),

		&m_pAntelopeFlagColor

	);



	resourcesCreated = true;

}



void CPlayState::buildFrameConstant() {
	for (std::list <CAgent *>::iterator agent = g_game->m_agents.begin(); agent != g_game->m_agents.end(); agent++)
		if ((*agent)->m_active)
			(*agent)->move();
}

