
#ifndef ESCAPESTATE_H
#define ESCAPESTATE_H

//#include "SDL.h"
#include "GameObjects\GameActors\Characters\Character.h"
#include "characterState.h"

#include "GameObjects\Flag.h"

class CEscapeState : public CStateBase
{
public:

	CEscapeState(CAgent* owner) :
		CStateBase(owner)

	{ }

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void Update();
	//void Draw(ID2D1HwndRenderTarget* renderTarget);

/*	static CFlagSeekState* Instance() {
		return &m_IdleState;
	}*/

	TVirtTime m_dirTick;
	TVirtTime m_minDirTick;
	void newDirection(TVirtTime minTick);
private:

	

};

#endif