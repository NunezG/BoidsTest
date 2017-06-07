
#include <stdio.h>

#include "gameManager.h"
#include "gamestate.h"
#include "introstate.h"
#include "playstate.h"
#include "../D2DHelper.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
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

	printf("CIntroState Init\n");


	HRESULT hr;
	ID2D1GeometrySink *pSink = NULL;

	// Create a path geometry.
	hr = D2DHelper::m_pD2DFactory->CreatePathGeometry(&m_pPathGeometry);

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

	pSink->AddLine(D2D1::Point2F(200, 0));

	pSink->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(150, 50),
			D2D1::Point2F(150, 150),
			D2D1::Point2F(200, 200))
	);

	pSink->AddLine(D2D1::Point2F(0, 200));

	pSink->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(50, 150),
			D2D1::Point2F(50, 50),
			D2D1::Point2F(0, 0))
	);

	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

	hr = pSink->Close();
}

SafeRelease(&pSink);





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
			GameManager::ChangeState(CPlayState::Instance());
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
	alpha--;

	if (alpha < 0)
		alpha = 0;

//	SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);
}

void CIntroState::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	HRESULT hr = S_OK;

	// Create a black brush.
	hr = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_pBlackBrush
	);
	
	if (SUCCEEDED(hr))
	{
		ID2D1GradientStopCollection *pGradientStops = NULL;
		// Create a linear gradient.
		static const D2D1_GRADIENT_STOP stops[] =
		{
			{ 0.f,{ 0.f, 1.f, 1.f, 0.25f } },
			{ 1.f,{ 0.f, 0.f, 1.f, 1.f } },
		};

		hr = renderTarget->CreateGradientStopCollection(
			stops,
			ARRAYSIZE(stops),
			&pGradientStops
		);
		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(100, 0),
					D2D1::Point2F(100, 200)),
				D2D1::BrushProperties(),
				pGradientStops,
				&m_pLinearGradientBrush
			);
			pGradientStops->Release();
		}
	}

	// Create a bitmap from an application resource.
	hr = D2DHelper::LoadResourceBitmap(
		renderTarget,
		D2DHelper::m_pWICFactory,
		L"SampleImage",
		L"Image",
		100,
		0,
		&m_pBitmap
	);
	if (SUCCEEDED(hr))
	{
		// Create a bitmap by loading it from a file.
		hr = D2DHelper::LoadBitmapFromFile(
			renderTarget,
			D2DHelper::m_pWICFactory,
			L".\\sampleImage.jpg",
			100,
			0,
			&m_pAnotherBitmap
		);
	}
	if (SUCCEEDED(hr))
	{
		hr = CreateGridPatternBrush(renderTarget, &m_pGridPatternBitmapBrush);
	}

	resourcesCreated = true;

}


void CIntroState::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	i++;

//	SDL_BlitSurface(bg, NULL, game->screen, NULL);

	// no need to blit if it's transparent
//	if ( alpha != 0 )
//		SDL_BlitSurface(fader, NULL, game->screen, NULL);

//	SDL_UpdateRect(game->screen, 0, 0, 0, 0);

	static const WCHAR sc_helloWorld[] = L"Hello, World!";


// Retrieve the size of the render target.
	D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();



	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	



	// Paint a grid background.
	renderTarget->FillRectangle(
		D2D1::RectF(0.0f, 0.0f, renderTargetSize.width, renderTargetSize.height),
		m_pGridPatternBitmapBrush
	);

	D2D1_SIZE_F size = m_pBitmap->GetSize();

	// Draw a bitmap in the upper-left corner of the window.
	renderTarget->DrawBitmap(
		m_pBitmap,
		D2D1::RectF(0.0f, 0.0f, size.width, size.height)
	);


	// Draw a bitmap at the lower-right corner of the window.
	size = m_pAnotherBitmap->GetSize();
	renderTarget->DrawBitmap(
		m_pAnotherBitmap,
		D2D1::RectF(
			renderTargetSize.width - size.width,
			renderTargetSize.height - size.height,
			renderTargetSize.width,
			renderTargetSize.height)
	);

	// Set the world transform to a 45 degree rotation at the center of the render target
	// and write "Hello, World".           

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
		D2DHelper::m_pTextFormat,
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		m_pBlackBrush
	);

	//
	// Reset back to the identity transform
	//
	renderTarget->SetTransform(
		D2D1::Matrix3x2F::Translation(0, renderTargetSize.height - 200)
	);

	// Fill the hour glass geometry with a gradient.
	renderTarget->FillGeometry(m_pPathGeometry, m_pLinearGradientBrush);

	renderTarget->SetTransform(
		D2D1::Matrix3x2F::Translation(renderTargetSize.width - 200, 0)
	);

	// Fill the hour glass geometry with a gradient.
	renderTarget->FillGeometry(m_pPathGeometry, m_pLinearGradientBrush);










}



//
// Creates a pattern brush.
//
HRESULT CIntroState::CreateGridPatternBrush(
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