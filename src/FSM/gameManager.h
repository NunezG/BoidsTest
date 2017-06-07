
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
#include "../SimpleDirect2dApplication.h"

using namespace std;

class CGameState;

class GameManager
{
public:

	static void Init(const char* title, int width=640, int height=480, 
		      int bpp=0, bool fullscreen=false);
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

	//SDL_Surface* screen;

private:
	// the stack of states
	static vector<CGameState*> states;

	static bool m_running;
	static bool m_fullscreen;
};

#endif
