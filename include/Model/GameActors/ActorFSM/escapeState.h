
#ifndef ESCAPESTATE_H
#define ESCAPESTATE_H

#include "stateBase.h"

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


private:

	

};

#endif