
#ifndef INTROSTATE_H
#define INTROSTATE_H

//#include "SDL.h"
#include "gamestate.h"
#include "Renderer/D2DHelper.h"

class CIntroState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(UINT message);
	void Update();
	void Draw(ID2D1HwndRenderTarget* renderTarget);
	void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

	static CIntroState* Instance() {
		return &m_IntroState;
	}

	HRESULT CreateGridPatternBrush(
		ID2D1RenderTarget *pRenderTarget,
		ID2D1BitmapBrush **ppBitmapBrush
	);


protected:
	CIntroState() { }

private:
	static CIntroState m_IntroState;

//	SDL_Surface* bg;
	//SDL_Surface* fader;
	int alpha;

	ID2D1BitmapBrush *m_pGridPatternBitmapBrush;
	ID2D1Bitmap *m_pBitmap;
	ID2D1Bitmap *m_pAnotherBitmap;
	ID2D1SolidColorBrush *m_pBlackBrush;

	float i = 0;


};

#endif