////////////////////////////////////////////////////////////////////////////////
// file: prey.cpp
// author: Radim Rehurek
// last update: 25.09.04
//
// prey is one type of agents, capable of eating grass
// its high-level behaviour is specified in brains.cpp
//////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <cassert>

#include "prey.h"
#include "Model\GameObjects\GameActors\agent.h"
#include "Model\game.h"
/*
///////////////////////////////////////////////////////////////////
// CPrey::CPrey
///////////////////////////////////////////////////////////////////
CPrey::CPrey() {
//    initialize();
    m_sight = 0.2f;
    m_walkSpeed = 0.15f;
//    m_type = PREY;
}
*/

///////////////////////////////////////////////////////////////////
// CPrey::processAgentConstant
// things that must be done every frame
///////////////////////////////////////////////////////////////////
int CPrey::processAgentConstant() {
    move();
   // graze();
    return 0;
}

///////////////////////////////////////////////////////////////////
// CPrey::processAgentPeriodic
// things that may be done at arbitrary frequency ("thinking")
// omitting to call this will result in unresponsive, dull agents but
// should not otherwise interfere with the simulation
///////////////////////////////////////////////////////////////////
int CPrey::processAgentPeriodic() {
  //  think();
//    m_lastUpdate = g_game->m_time->tickNow();
    return 0;
}

