#ifndef _prey_h_
#define _prey_h_

#include "Model\GameObjects\GameActors\agent.h"

class CPrey : public CAgent {
protected:
    float m_grazeSpeed;
public:
  //  CPrey();
    int processAgentConstant();
    int processAgentPeriodic();


    void drawAgent() const; // defined in gfx.cpp
   
};

#endif
