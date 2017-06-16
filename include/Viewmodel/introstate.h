
#ifndef INTROSTATE_H
#define INTROSTATE_H

//#include "SDL.h"
#include "gamestate.h"
#include "View/D2DHelper.h"

class CIntroState : public CGameState
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

	static CIntroState* Instance() {
		return &m_IntroState;
	}

	void buildFrameConstant() {}
	int buildFramePeriodic() { return 0; }

protected:
	CIntroState() { }

private:
	static CIntroState m_IntroState;

};

#endif