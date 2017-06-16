
#ifndef FLAGRETURN_H
#define FLAGRETURN_H

#include "Model\GameObjects\GameActors\CharacterFSM.h"
#include "Model\GameObjects\GameActors\StartPosition.h"

#include "Model\GameObjects\Flag.h"
#include "Model\virtualtime.h"
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

	TVirtTime m_minDirTick;
	TVirtTime m_dirTick;
};

#endif