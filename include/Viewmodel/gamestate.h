

#ifndef ITGAMESTATE_H
#define ITGAMESTATE_H

#include "View/D2DHelper.h"
#include "GameStatesManager.h"


class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(UINT message) = 0;
	virtual void Update() = 0;
	virtual void buildFrameConstant() = 0;

	virtual void Draw() = 0;
	virtual void CreateMaterials() = 0;
	bool resourcesCreated;

protected:
	CGameState() { }
};

#endif