
#ifndef MENUSTATE_H
#define MENUSTATE_H

//#include "SDL.h"
#include "gamestate.h"

class CPauseState : public CGameState
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

	static CPauseState* Instance() {
		return &m_MenuState;
	}

	void buildFrameConstant() {}
	int buildFramePeriodic() { return 0; }

protected:
	CPauseState() { }

private:
	static CPauseState m_MenuState;
};

#endif