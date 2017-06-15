
#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

#include "stateBase.h"

class CCharacterState : public CStateBase
{
public:
	

	//void ChangeState(CCharacterState* state);

	CCharacterState(CAgent* owner) :CStateBase(owner){ }

protected:
};

#endif