
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
#include "../gameManager.h"
#include "../GameObjects/Characters/Character.h"

using namespace std;

class CGameState;

class CObjectManager
{
public:

	static void Init(const char* title, int width=640, int height=480, 
		      int bpp=0, bool fullscreen=false);

	static void Cleanup();

//	static void ChangeState(CGameState* state);
//	static void PushObject(CGameState* state);
//	static void PopObject();

//	static void HandleEvents(UINT message);
//	static void Update();
//	static void Draw(ID2D1HwndRenderTarget* renderTarget);
//	static void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

	//static bool Running() { return m_running; }
	//static void Quit() { m_running = false; }

	//SDL_Surface* screen;

private:
	// the stack of states

	static bool m_fullscreen;
};

#endif
