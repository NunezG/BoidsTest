
#ifndef FLAGSEEKSTATE_H
#define FLAGSEEKSTATE_H

#include "stateBase.h"
#include "Model\GameActors\flagStand.h"
#include "Model\GameActors\flag.h"

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

private:

	CFlag* m_pTargetFlag;
	CFlagStand* m_homeStand;

};

#endif