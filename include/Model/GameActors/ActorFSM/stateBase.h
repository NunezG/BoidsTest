
#ifndef STATEBASE_H
#define STATEBASE_H

#include "../agent.h"


class CStateBase
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Update() = 0;

	CStateBase(CAgent* owner): m_Owner(owner){ }


protected:
	CAgent* m_Owner;

};

#endif