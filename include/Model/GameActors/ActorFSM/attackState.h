
#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H

#include "stateBase.h"


class CAttackState : public CStateBase
{
public:
	CAttackState(CAgent* owner, CAgent* targetAgent) :
		CStateBase(owner )
		, m_targetAgent(targetAgent)
	{ }

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void Update();

private:
	CAgent* m_targetAgent;
};

#endif