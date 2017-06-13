

#ifndef _SeesEnemy_H_
#define _SeesEnemy_H_

#include "ieexec.h"

class SeesEnemy : public IEExec {
public:
    SeesEnemy();
    void init   ( CAgent * owner );
    bool update ();
    CAgent * getOwner ();
    const char * getName();

private:
    CAgent * findNearestVisibleEnemy();
    std::string m_name;
    CAgent * m_owner;
};

#endif
