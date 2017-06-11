
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
#include "Renderer\D2DRenderer.h"
//#include "FSM\Game\gamestate.h"
//#include "FSM\Game\playstate.h"

//#include "Renderer\Window.h"

#include "Renderer\Window.h"

using namespace std;

class CGameState;

class GameManager
{
public:

	static bool Init(const char* title, int width=640, int height=480, 
		      int bpp=0, bool fullscreen=false);
	//static void Cleanup();

	//static void HandleEvents(UINT message);
	//static void Update();
	//static void Draw(ID2D1HwndRenderTarget* renderTarget);
	//static void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

	static bool Running() { return m_running; }
	static void Quit() { m_running = false; }

	static void RunMessageLoop();

	//SDL_Surface* screen;
	static void Tick();

private:

	static bool m_running;
	static bool m_fullscreen;

	static CITWindow* TestWindow;

	static DemoApp* myApplication;



	static double m_dStartTime;

	static double m_dDeltaTime;


	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);


};

#endif
