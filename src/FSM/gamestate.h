
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gameManager.h"

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
	virtual void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget) = 0;
	bool resourcesCreated;

	void ChangeState(CGameState* state) {
		GameManager::ChangeState(state);
	}

protected:
	CGameState() { }
};

#endif