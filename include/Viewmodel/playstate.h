
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

//#include "SDL.h"
#include "gamestate.h"
//#include "menustate.h"

//#include "SDL.h"

//class CIntroState;

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
	void CreateMaterials(ID2D1HwndRenderTarget* renderTarget);

	static CPlayState* Instance() {
		return &m_PlayState;
	}
	void CreateFlag();

	void buildFrameConstant();
	int buildFramePeriodic();

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

	ID2D1SolidColorBrush*	m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush*	m_pAntelopeTeamColor;
	ID2D1SolidColorBrush*	m_pLionTeamColor;

	ID2D1SolidColorBrush*	m_pAntelopeFlagColor;
	ID2D1SolidColorBrush*	m_pLionFlagColor;
	ID2D1PathGeometry *m_pPathGeometry;

	int counter[2];

//	SDL_Surface* bg;
};

#endif
