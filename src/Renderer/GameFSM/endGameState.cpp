#include "Renderer\GameFSM\endGameState.h"
//#include "playstate.h"

CEndGameState CEndGameState::m_EndGameState;

#include "Renderer\GameFSM\PlayState.h";

void CEndGameState::Init()
{
	resourcesCreated = false;
	//SDL_Surface* temp = SDL_LoadBMP("intro.bmp");

//	bg = SDL_DisplayFormat(temp);

//	SDL_FreeSurface(temp);

	// create the fader surface like the background with alpha
//	fader = SDL_CreateRGBSurface( SDL_SRCALPHA, bg->w, bg->h, 
//								  bg->format->BitsPerPixel, 
//								  bg->format->Rmask, bg->format->Gmask, 
//								  bg->format->Bmask, bg->format->Amask );

	// fill the fader surface with black
//	SDL_FillRect (fader, NULL, SDL_MapRGB (bg->format, 0, 0, 0)) ;

	// start off opaque
	alpha = 255;

//	SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

	printf("CEndGameState Init\n");





}


void CEndGameState::Cleanup()
{
//	SDL_FreeSurface(bg);
//	SDL_FreeSurface(fader);

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

void CEndGameState::Update() 
{
	alpha--;

	if (alpha < 0)
		alpha = 0;

//	SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);
}

void CEndGameState::CreateMaterials(ID2D1HwndRenderTarget* renderTarget)
{
	HRESULT hr = S_OK;

	
	if (SUCCEEDED(hr))
	{
		hr = CreateGridPatternBrush(renderTarget, &m_pGridPatternBitmapBrush);
	}

	resourcesCreated = true;

}


void CEndGameState::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	i++;

//	SDL_BlitSurface(bg, NULL, game->screen, NULL);

	// no need to blit if it's transparent
//	if ( alpha != 0 )
//		SDL_BlitSurface(fader, NULL, game->screen, NULL);

//	SDL_UpdateRect(game->screen, 0, 0, 0, 0);

	static const char sc_helloWorld[] = "LIONS VS ANTELOPES";


// Retrieve the size of the render target.
	D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();



	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	



	// Paint a grid background.
	renderTarget->FillRectangle(
		D2D1::RectF(0.0f, 0.0f, renderTargetSize.width, renderTargetSize.height),
		m_pGridPatternBitmapBrush
	);

	//D2D1_SIZE_F size = m_pBitmap->GetSize();



	CD2DHelper::outText(0, -300, sc_helloWorld);


	// Set the world transform to a 45 degree rotation at the center of the render target
	// and write "Hello, World".           
/*
	const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(
		i * 10,
		D2D1::Point2F(
			renderTargetSize.width / 2,
			renderTargetSize.height / 2));

	const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(-200, 3);

	renderTarget->SetTransform(rot * trans);
	
	renderTarget->DrawText(
		sc_helloWorld,
		ARRAYSIZE(sc_helloWorld) - 1,
		CD2DHelper::m_pTextFormat,
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		m_pBlackBrush
	);

	




	*/



}



//
// Creates a pattern brush.
//
HRESULT CEndGameState::CreateGridPatternBrush(
	ID2D1RenderTarget *pRenderTarget,
	ID2D1BitmapBrush **ppBitmapBrush
)
{
	HRESULT hr = S_OK;

	// Create a compatible render target.
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	hr = pRenderTarget->CreateCompatibleRenderTarget(
		D2D1::SizeF(10.0f, 10.0f),
		&pCompatibleRenderTarget
	);
	if (SUCCEEDED(hr))
	{
		// Draw a pattern.
		ID2D1SolidColorBrush *pGridBrush = NULL;
		hr = pCompatibleRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF(0.93f, 0.94f, 0.96f, 1.0f)),
			&pGridBrush
		);
		if (SUCCEEDED(hr))
		{
			pCompatibleRenderTarget->BeginDraw();
			pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, 10.0f, 1.0f), pGridBrush);
			pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.1f, 1.0f, 10.0f), pGridBrush);
			pCompatibleRenderTarget->EndDraw();

			// Retrieve the bitmap from the render target.
			ID2D1Bitmap *pGridBitmap = NULL;
			hr = pCompatibleRenderTarget->GetBitmap(&pGridBitmap);
			if (SUCCEEDED(hr))
			{
				// Choose the tiling mode for the bitmap brush.
				D2D1_BITMAP_BRUSH_PROPERTIES brushProperties =
					D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP);

				// Create the bitmap brush.
				hr = pRenderTarget->CreateBitmapBrush(pGridBitmap, brushProperties, ppBitmapBrush);

				pGridBitmap->Release();
			}

			pGridBrush->Release();
		}

		pCompatibleRenderTarget->Release();
	}

	return hr;
}