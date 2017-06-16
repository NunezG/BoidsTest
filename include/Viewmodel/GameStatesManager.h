
#ifndef GAMESTATESMANAGER_H
#define GAMESTATESMANAGER_H

#include <vector>
#include "View/d2dHelper.h"

class CGameState;

using namespace std;

class CGameStatesManager
{
public:

	static bool Init();
	static void Cleanup();

	static void ChangeState(CGameState* state);
	static void PushState(CGameState* state);
	static void PopState();

	static void HandleEvents(UINT message);
	static void Update();
	static void Draw();
	static void CreateDeviceResources();

	static bool Running() { return m_running; }
	static void Quit() { m_running = false; }


private:
	// the stack of states
	static vector<CGameState*> states;

	static bool m_running;

};

#endif
