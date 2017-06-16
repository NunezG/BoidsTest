
#ifndef ESCAPESTATE_H
#define ESCAPESTATE_H

#include "Model\GameObjects\GameActors\agent.h"
#include "Model\virtualtime.h"
#include "Model\GameObjects\Flag.h"

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

	TVirtTime m_dirTick;
	TVirtTime m_minDirTick;
private:

	

};

#endif