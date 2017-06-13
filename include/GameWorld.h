
#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <vector>
//#include "introstate.h"
//#include "menustate.h"
//#include "playstate.h"
#include "Renderer\D2DRenderer.h"
//#include "CGameWorld.h"
#include "GameObjects/GameActors/Characters/Character.h"
#include "GameObjects/Flag.h"
#include "GameObjects\ObjectManager.h" 


using namespace std;

class CGameState;

class CGameWorld
{
public:

	static bool Init(const char* title, int width=640, int height=480, 
		      int bpp=0, bool fullscreen=false);

	static void Cleanup();


	static void HandleEvents(UINT message);
	static void Update();
	static void Draw(ID2D1HwndRenderTarget* renderTarget);
	static void CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

	static bool Running() { return m_running; }
	static void Quit() { m_running = false; }

	//SDL_Surface* screen;
	//static CObjectManager* m_objectManager;

	


private:


	//static vector<CCharacter*> m_characters;
	static vector<CFlag*> m_teamFlags;

	static bool m_running;
};

#endif
