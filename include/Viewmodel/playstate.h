
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

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
	void Draw();
	void CreateMaterials();

	static CPlayState* Instance() {
		return &m_PlayState;
	}

	void buildFrameConstant();

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

	ID2D1SolidColorBrush*	m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush*	m_pAntelopeTeamColor;
	ID2D1SolidColorBrush*	m_pLionTeamColor;

	ID2D1SolidColorBrush*	m_pAntelopeFlagColor;
	ID2D1SolidColorBrush*	m_pLionFlagColor;

	float s_speed = 10.f; // initial simulation speed
};

#endif
