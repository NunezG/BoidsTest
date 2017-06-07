
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

//#include "SDL.h"
#include "gamestate.h"

class CPlayState : public CGameState
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

	static CPlayState* Instance() {
		return &m_PlayState;
	}

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

	ID2D1SolidColorBrush*	m_pLightSlateGrayBrush;
//	SDL_Surface* bg;
};

#endif
