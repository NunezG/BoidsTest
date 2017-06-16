
#ifndef ENDGAMESTATE_H
#define ENDGAMESTATE_H

//#include "SDL.h"
#include "gamestate.h"
#include "View/D2DHelper.h"

class CEndGameState : public CGameState
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

	static CEndGameState* Instance() {
		return &m_EndGameState;
	}


	void buildFrameConstant(){}
	int buildFramePeriodic() { return 0; }

protected:
	CEndGameState() { }

private:
	static CEndGameState m_EndGameState;



	float i = 0;


};

#endif