
#ifndef RETURNTOHOME_H
#define RETURNTOHOME_H

//#include "SDL.h"
#include "Model\GameObjects\GameActors\CharacterFSM.h"
#include "Model\GameObjects\GameActors\StartPosition.h"

#include "Model\GameObjects\Flag.h"
#include "Model\virtualtime.h"
class CReturnToHomeState : public CStateBase
{
public:

	CReturnToHomeState(CAgent* owner, CFlag* flag, CFlagStand* stand) :
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


private:

	CFlag* m_pTargetFlag;
	CFlagStand* m_homeStand;

	TVirtTime m_minDirTick;
	TVirtTime m_dirTick;

};

#endif