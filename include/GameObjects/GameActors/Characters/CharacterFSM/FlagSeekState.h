
#ifndef FLAGSEEKSTATE_H
#define FLAGSEEKSTATE_H

//#include "SDL.h"
#include "GameObjects\GameActors\Characters\Character.h"
#include "characterState.h"

#include "GameObjects\Flag.h"

class CFlagSeekState : public CStateBase
{
public:

	CFlagSeekState(CCharacter* owner, CFlag* flag) :
		CStateBase()
		,m_Owner(owner)
		, m_pTargetFlag(flag)
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
	CCharacter* m_Owner;


private:

	CFlag* m_pTargetFlag;


};

#endif