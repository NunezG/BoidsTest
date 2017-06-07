
#ifndef MENUSTATE_H
#define MENUSTATE_H

//#include "SDL.h"
#include "gamestate.h"

class CMenuState : public CGameState
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

	static CMenuState* Instance() {
		return &m_MenuState;
	}

protected:
	CMenuState() { }

private:
	static CMenuState m_MenuState;

	//SDL_Surface* bg;
};

#endif