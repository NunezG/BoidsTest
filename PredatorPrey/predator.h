#ifndef _predator_h_
#define _predator_h_

#include "Model\GameObjects\GameActors\agent.h"

class CPredator : public CAgent {
public:
//	CPredator();
	int processAgentConstant();
	int processAgentPeriodic();
	void makeBrain();

	void drawAgent() const; // defined in gfx.cpp
};

#endif
