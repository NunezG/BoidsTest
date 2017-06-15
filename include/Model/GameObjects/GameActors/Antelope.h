
#ifndef ANTELOPE_H
#define ANTELOPE_H

#include "agent.h"



class CAntelope : public CAgent
{

private:
	//bool m_bAlive;

public:
	CAntelope::CAntelope(CFlagStand* TeamStand, CFlag* enemyFlag);
	// engine routines
	int processAgentConstant();
	int processAgentPeriodic();
	//void move();

	bool attackCondition();
	bool retreatCondition();


};

#endif
