

#ifndef ITGAMESTATE_H
#define ITGAMESTATE_H

#include "Renderer/D2DHelper.h"
#include "GameStatesManager.h"

enum EGameState
{
	Intro,
	Play,
	Pause,
	End
};

class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(UINT message) = 0;
	virtual void Update() = 0;
	virtual void Draw(ID2D1HwndRenderTarget* renderTarget) = 0;
	virtual void CreateMaterials(ID2D1HwndRenderTarget* renderTarget) = 0;
	bool resourcesCreated;

	void ChangeState(CGameState* state) {
		CGameStatesManager::ChangeState(state);

	}

protected:
	CGameState() { }
};

#endif