
#ifndef lion_H
#define lion_H

#include "agent.h"



class CLion : public CAgent
{

private:
	//bool m_bAlive;

public:
	CLion::CLion(CFlagStand* TeamStand, CFlag* enemyFlag);
	// engine routines
	int processAgentConstant();
	int processAgentPeriodic();
	//void move();

	bool attackCondition();
	bool retreatCondition();
};

#endif
