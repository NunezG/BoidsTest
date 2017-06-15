
#ifndef FLAGSEEKSTATE_H
#define FLAGSEEKSTATE_H

//#include "SDL.h"
#include "GameObjects\GameActors\Characters\Character.h"
#include "characterState.h"

#include "GameObjects\Flag.h"
#include "virtualtime.h"
class CFlagSeekState : public CStateBase
{
public:

	CFlagSeekState(CAgent* owner, CFlag* flag, CFlagStand* stand) :
		CStateBase(owner)
		, m_pTargetFlag(flag)
		, m_homeStand(stand)
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
	void newDirection(TVirtTime minTick);


private:

	CFlag* m_pTargetFlag;
	CFlagStand* m_homeStand;

	TVirtTime m_minDirTick;
	TVirtTime m_dirTick;

};

#endif