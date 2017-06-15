

#include "Viewmodel\playstate.h"
#include "Viewmodel\introstate.h"

#include "Viewmodel\endGameState.h"
//#include "GameObjects\ObjectManager.h"
#include "Model\GameObjects\ObjectManager.h"
#include <string>
#include <cmath>
#include "Model\game.h"
#include "Model\GameObjects\GameActors\agent.h"


CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
	g_model = new CObjectManager();

	g_model->Init();

	resourcesCreated = false;

	CreateFlag();
	//SDL_Surface* temp = SDL_LoadBMP("play.bmp");

//	bg = SDL_DisplayFormat(temp);

//	SDL_FreeSurface(temp);

	printf("CPlayState Init\n");
}

void CPlayState::Cleanup()
{
	//SDL_FreeSurface(bg);

	printf("CPlayState Cleanup\n");
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
}

void CPlayState::HandleEvents(UINT message)
{

	switch (message)
	{
	case WM_KEYDOWN:
		CGameStatesManager::ChangeState(CIntroState::Instance());
		break;


	}
	//SDL_Event event;

/*	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game->Quit();
						break;
					case SDLK_m:
						game->PushState( CMenuState::Instance() );
						break;
				}
				break;
		}
	}
	*/
}

void CPlayState::Update()
{

	g_model->Update();


	//Point conditions
	if ((g_model->m_pFlags[0]->getOwner()->getPosition() - g_model->stands[1].getPosition()).length() < 50)
	{
		counter[0]++;
		g_model->m_pFlags[0]->setOwner(&g_model->stands[0]);
		printf("Antelopes COUNTER: \n");
		printf((char*)counter[0]);

		printf(" \n");


	}

	if ((g_model->m_pFlags[1]->getOwner()->getPosition() - g_model->stands[0].getPosition()).length() < 50)
	{
		counter[1]++;
		g_model->m_pFlags[1]->setOwner(&g_model->stands[1]);
		printf("Lions COUNTER: \n");
		printf((char*)counter[0]);

		printf(" \n");


	}


	//End Game rule
	if (counter[0] >= 5 && counter[1] >= 5)
		CGameStatesManager::ChangeState(CEndGameState::Instance());

	//TestWindow->OnRender();
}

void CPlayState::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

	// Draw a grid background.
	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);

	for (int x = 0; x < width; x += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			m_pLightSlateGrayBrush,
			0.5f
		);
	}

	for (int y = 0; y < height; y += 10)
	{
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			m_pLightSlateGrayBrush,
			0.5f
		);
	}

	for (std::list <CAgent *>::iterator _agent = g_model->m_agents.begin(); _agent != g_model->m_agents.end(); _agent++) {
		CAgent *agent = (*_agent);
		if (agent->m_active) {

			Vector2d poisiton = agent->getPosition();
			ID2D1SolidColorBrush*	characterColor;


			if (agent->GetTeam() == antelopesTeam)
				characterColor = m_pAntelopeTeamColor;
			else
				characterColor = m_pLionTeamColor;



			CD2DHelper::Rectange(200, characterColor, poisiton.m_x, poisiton.m_y, std::atan2(agent->getVelocity().m_x, agent->getVelocity().m_y));
			/*

			if (g_model->m_oCharacters[i]->HasFlag())
			{
				ID2D1SolidColorBrush*	flagColor;

				if (g_model->m_oCharacters[i]->GetTeam() == antelopesTeam)
					flagColor = m_pAntelopeFlagColor;
				else
					flagColor = m_pLionFlagColor;

				CD2DHelper::Rectange(100, flagColor, g_model->m_oCharacters[i]->getPosition().m_x, g_model->m_oCharacters[i]->getPosition().m_y);
			}
			*/
		}
	}


	//D2D1_COLOR_F color;

	
	//m_pLightSlateGrayBrush->SetColor(D2D1::ColorF(14, 1));

//	m_pTestBrush->SetColor(D2D1::ColorF(7, 1));


	//g_model->stands[0]->GetLocation().X = 120.0f;

	CD2DHelper::Rectange(50, m_pAntelopeTeamColor, g_model->stands[0].getPosX(), g_model->stands[0].getPosY());
	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

//	CD2DHelper::Rectange(200, m_pTestBrush, 120.0f , 60.0f);


	CD2DHelper::Rectange(50, m_pLionTeamColor, g_model->stands[1].getPosX(), g_model->stands[1].getPosY());
//	D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();



	D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();


//
// Reset back to the identity transform
//
/*	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Translation(0, renderTargetSize.height - 200)
	);

	// Fill the hour glass geometry with a gradient.
	m_pRenderTarget->FillGeometry(m_pPathGeometry, m_pAntelopeFlagColor);

	m_pRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Translation(renderTargetSize.width - 200, 0)
	);

	// Fill the hour glass geometry with a gradient.
	m_pRenderTarget->FillGeometry(m_pPathGeometry, m_pLionFlagColor);

*/
	//CD2DHelper::Showtext(L"TEXT!", 5);



	if (g_model->m_pFlags[0])
		CD2DHelper::Rectange(100, m_pAntelopeFlagColor, g_model->m_pFlags[0]->getOwner()->getPosX(), g_model->m_pFlags[0]->getOwner()->getPosY());

	if (g_model->m_pFlags[1])
		CD2DHelper::Rectange(100, m_pLionFlagColor, g_model->m_pFlags[1]->getOwner()->getPosX(), g_model->m_pFlags[1]->getOwner()->getPosY());

	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());


//	const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(g_model->stands[1]->GetLocation().X, g_model->stands[1]->GetLocation().Y);

//	m_pRenderTarget->SetTransform(trans);
	
	//std::wstring s = std::wstring("file_") + std::to_wstring(i) + std::wstring(".dat");
	//std::wstring::to
//	std::wstring sss = L"";

//	sss.c_str

//	std::string s;

	//s.c_str();



	//SDL_BlitSurface(bg, NULL, game->screen, NULL);
	//SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}


void CPlayState::CreateMaterials(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	HRESULT hr = S_OK;


	// Create a gray brush.

	hr = m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Gray),

		&m_pLightSlateGrayBrush

	);

	hr = m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::YellowGreen),

		&m_pLionTeamColor

	);

	hr = m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Maroon),

		&m_pAntelopeTeamColor

	);

	hr = m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Yellow),

		&m_pLionFlagColor

	);


	hr = m_pRenderTarget->CreateSolidColorBrush(

		D2D1::ColorF(D2D1::ColorF::Red),

		&m_pAntelopeFlagColor

	);



	resourcesCreated = true;

}


void CPlayState::CreateFlag()
{
	HRESULT hr;
	ID2D1GeometrySink *pSink = NULL;

	// Create a path geometry.
	hr = CD2DHelper::m_pD2DFactory->CreatePathGeometry(&m_pPathGeometry);

	if (SUCCEEDED(hr))
	{
		// Use the geometry sink to write to the path geometry.
		hr = m_pPathGeometry->Open(&pSink);
	}
	if (SUCCEEDED(hr))
	{
		pSink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);

		pSink->BeginFigure(
			D2D1::Point2F(0, 0),
			D2D1_FIGURE_BEGIN_FILLED
		);

		pSink->AddLine(D2D1::Point2F(20, 0));

		pSink->AddBezier(
			D2D1::BezierSegment(
				D2D1::Point2F(15, 5),
				D2D1::Point2F(15, 15),
				D2D1::Point2F(20, 20))
		);

		pSink->AddLine(D2D1::Point2F(0, 20));

		pSink->AddBezier(
			D2D1::BezierSegment(
				D2D1::Point2F(5, 15),
				D2D1::Point2F(5, 5),
				D2D1::Point2F(0, 0))
		);

		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
	}

	SafeRelease(&pSink);



}

void CPlayState::buildFrameConstant() {
	for (std::list <CAgent *>::iterator agent = g_model->m_agents.begin(); agent != g_model->m_agents.end(); agent++)
		if ((*agent)->m_active)
			(*agent)->processAgentConstant();
}


///////////////////////////////////////////////////////////////////
// CGame::buildFramePeriodic
// do some not-so-urgent work
///////////////////////////////////////////////////////////////////
int CPlayState::buildFramePeriodic() {
	for (std::list <CAgent*>::iterator agent = g_model->m_agents.begin(); agent != g_model->m_agents.end(); agent++) {
		if (((*agent))->m_active)
			((*agent))->processAgentPeriodic();
	}

	return 0;
}