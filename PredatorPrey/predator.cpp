////////////////////////////////////////////////////////////////////////////////
// file: predator.cpp
// author: Radim Rehurek
// last update: 25.09.04
//
// predator is one type of agents. its high-level behaviour is specified in brains.cpp
// unlike prey, it does not bring any new abilities to CAgent and only implements its abstract methods
//////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include "predator.h"
#include "agent.h"
#include "game.h"

#include "agent.h"
#include "agentbrainlib.h"
#include "prey.h"
#include "predator.h"

/*
///////////////////////////////////////////////////////////////////
// CPredator::CPredator
///////////////////////////////////////////////////////////////////
CPredator::CPredator() {
   // initialize();
    m_sight = 0.25f;
    m_walkSpeed = 0.08f;
  //  m_type = PREDATOR;
}
*/
///////////////////////////////////////////////////////////////////
// CPredator::processAgentConstant
// things that must be done every frame
///////////////////////////////////////////////////////////////////
int CPredator::processAgentConstant() {
    move();
    return 0;
}

///////////////////////////////////////////////////////////////////
// CPredator::processAgentPeriodic
// things that may be done at arbitrary frequency ("thinking")
// omitting to call this will result in unresponsive, dull agents but
// should not otherwise interfere with the simulation
///////////////////////////////////////////////////////////////////
int CPredator::processAgentPeriodic() {
  //  think();
    m_lastUpdate = g_game->m_time->tickNow();
    return 0;
}




void CPredator::makeBrain()
{
/*	char lineInfo[256];
	IEExec * exec;
	IE * ie = new IE;
	ie->start(name, this);



	//AL(Wander)
    exec = new Wander();
	ie->makeGoal(exec);

#define IF(execClass)\
    exec = new execClass;\
    sprintf ( lineInfo, "File:%s Line %d", __FILE__, __LINE__ );\
	ie->makeRule(exec, lineInfo);

#define IF_DONE\
    ie->makeDoneRule();

#define GOTO(goal)\
    sprintf ( lineInfo, "File:%s Line %d", __FILE__, __LINE__ );\
	ie->addRuleGoto(#goal, lineInfo);

#define GOSUB(goal)\
    sprintf ( lineInfo, "File:%s Line %d", __FILE__, __LINE__ );\
	ie->addRuleGosub(#goal, lineInfo);

#define RETURN\
    sprintf ( lineInfo, "File:%s Line %d", __FILE__, __LINE__ );\
	ie->addRuleReturn(lineInfo);

#define IE_END \
	ie->end(); \
    m_brain = ie; \
	*/

}
