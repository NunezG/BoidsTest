
#ifndef FLAGRETURN_H
#define FLAGRETURN_H

#include "stateBase.h"
#include "Model\GameActors\flagStand.h"
#include "Model\GameActors\flag.h"

class CFlagReturnState : public CStateBase
{
public:

	CFlagReturnState(CAgent* owner, CFlag* flag, CFlagStand* stand) :
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