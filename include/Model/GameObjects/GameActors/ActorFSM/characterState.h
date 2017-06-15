
#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

#include "stateBase.h"

class CCharacterFSMState : public CStateBase
{
public:
	

	//void ChangeState(CCharacterFSMState* state);

	CCharacterFSMState(CAgent* owner) :CStateBase(owner){ }

protected:
};

#endif