

#include "Renderer\GameFSM\playstate.h"
#include "Renderer\GameFSM\introstate.h"
//#include "GameObjects\ObjectManager.h"
#include "GameWorld.h"
#include <string>


CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
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
	CObjectManager::Update();
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

	for (std::list <CAgent *>::iterator _agent = CObjectManager::m_agents.begin(); _agent != CObjectManager::m_agents.end(); _agent++) {
		CAgent *agent = *_agent;
		if (agent->m_active && ((CCharacter*)agent)->isAlive()) {

			Vector2d poisiton = agent->getPosition();
			ID2D1SolidColorBrush*	characterColor;


			if (agent->GetTeam() == antelopesTeam)
				characterColor = m_pAntelopeTeamColor;
			else
				characterColor = m_pLionTeamColor;

			CD2DHelper::Rectange(200, characterColor, poisiton.m_x, poisiton.m_y);
			/*

			if (CObjectManager::m_oCharacters[i]->HasFlag())
			{
				ID2D1SolidColorBrush*	flagColor;

				if (CObjectManager::m_oCharacters[i]->GetTeam() == antelopesTeam)
					flagColor = m_pAntelopeFlagColor;
				else
					flagColor = m_pLionFlagColor;

				CD2DHelper::Rectange(100, flagColor, CObjectManager::m_oCharacters[i]->getPosition().m_x, CObjectManager::m_oCharacters[i]->getPosition().m_y);
			}
			*/
		}
	}


	//D2D1_COLOR_F color;

	
	//m_pLightSlateGrayBrush->SetColor(D2D1::ColorF(14, 1));

//	m_pTestBrush->SetColor(D2D1::ColorF(7, 1));


	//CObjectManager::stands[0]->GetLocation().X = 120.0f;

	CD2DHelper::Rectange(50, m_pAntelopeTeamColor, CObjectManager::stands[0]->initialPosition.m_x, CObjectManager::stands[0]->initialPosition.m_y);
	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

//	CD2DHelper::Rectange(200, m_pTestBrush, 120.0f , 60.0f);


	CD2DHelper::Rectange(50, m_pLionTeamColor, CObjectManager::stands[1]->initialPosition.m_x, CObjectManager::stands[1]->initialPosition.m_y);
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



	if (CObjectManager::m_pFlags[0])
		CD2DHelper::Rectange(100, m_pAntelopeFlagColor, CObjectManager::m_pFlags[0]->getOwner()->initialPosition.m_x, CObjectManager::m_pFlags[0]->getOwner()->initialPosition.m_y);

	if (CObjectManager::m_pFlags[1])
		CD2DHelper::Rectange(100, m_pLionFlagColor, CObjectManager::m_pFlags[1]->getOwner()->initialPosition.m_x, CObjectManager::m_pFlags[1]->getOwner()->initialPosition.m_y);

	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());


//	const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(CObjectManager::stands[1]->GetLocation().X, CObjectManager::stands[1]->GetLocation().Y);

//	m_pRenderTarget->SetTransform(trans);
	
	//std::wstring s = std::wstring("file_") + std::to_wstring(i) + std::wstring(".dat");
	//std::wstring::to
//	std::wstring sss = L"";

//	sss.c_str

//	std::string s;

	//s.c_str();
	std::wstring num = 	std::to_wstring((int)CObjectManager::stands[1]->initialPosition.m_x);
	;

	wchar_t number = (int)CObjectManager::stands[1]->initialPosition.m_x;
	wchar_t number2 = (int)CObjectManager::stands[0]->initialPosition.m_x;
	wchar_t number3 = (int)CObjectManager::stands[0]->initialPosition.m_y;

	
	 WCHAR sc_helloWorld[] = L"sfdsdsNUM:cccfhgs ";

	sc_helloWorld[1] = number;
	sc_helloWorld[2] = number2;
	sc_helloWorld[3] = number3;

	/*
	m_pRenderTarget->DrawText(
		sc_helloWorld,
		ARRAYSIZE(sc_helloWorld) -1,
		CD2DHelper::m_pTextFormat,
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		m_pTestBrush
	);

	*/

	//CD2DHelper::Rectange(m_pLightSlateGrayBrush, 100, -50);

	// Draw two rectangles.
/*	D2D1_RECT_F rectangle1 = D2D1::RectF(
		rtSize.width / 2 - 50.0f,
		rtSize.height / 2 - 50.0f,
		rtSize.width / 2 + 50.0f,
		rtSize.height / 2 + 50.0f
	);
	*/
/*	D2D1_RECT_F rectangle2 = D2D1::RectF(
		rtSize.width / 2 - 100.0f,
		rtSize.height / 2 - 100.0f,
		rtSize.width / 2 + 100.0f,
		rtSize.height / 2 + 100.0f
	);
*/

	// Draw a filled rectangle.
//	m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);

	// Draw the outline of a rectangle.
	//m_pRenderTarget->DrawRectangle(&rectangle2, m_pLightSlateGrayBrush);

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