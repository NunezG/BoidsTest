
#ifndef GAMESTATESMANAGER_H
#define GAMESTATESMANAGER_H

#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
#include "View/D2DHelper.h"
//#include "FSM\Game\gamestate.h"
//#include "FSM\Game\playstate.h"

//class CITWindow;

class CGameState;

using namespace std;

//class CGameState;

class CGameStatesManager
{
public:

	static bool Init(const char* title, int width = 640, int height = 480,
		int bpp = 0, bool fullscreen = false);
	static void Cleanup();

	static void ChangeState(CGameState* state);
	static void PushState(CGameState* state);
	static void PopState();

	static void HandleEvents(UINT message);
	static void Update();
	static void Draw(ID2D1HwndRenderTarget* renderTarget);
	static void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

	static bool Running() { return m_running; }
	static void Quit() { m_running = false; }



	static void buildFrameConstant();
	static void buildFramePeriodic();


	//static void RunMessageLoop();

	//SDL_Surface* screen;
	//static void Tick();

private:
	// the stack of states
	static vector<CGameState*> states;

	static bool m_running;
	//static bool m_fullscreen;

};

#endif
