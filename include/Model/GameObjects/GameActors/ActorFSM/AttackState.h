
#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H

//#include "SDL.h"
#include "../agent.h"


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
	//void Draw(ID2D1HwndRenderTarget* renderTarget);


	//CAttackState() { }

private:
	CAgent* m_targetAgent;
};

#endif