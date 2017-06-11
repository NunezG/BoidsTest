
#ifndef STATEBASE_H
#define STATEBASE_H

#include "gameManager.h"

class CStateBase
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	//virtual void HandleEvents(UINT message) = 0;
	virtual void Update() = 0;
	//virtual void Draw(ID2D1HwndRenderTarget* renderTarget) = 0;
	//virtual void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget) = 0;
	//bool resourcesCreated;

	void ChangeState(CStateBase* state) {
		//GameManager::ChangeState();
	}

	CStateBase() { }

protected:
};

#endif