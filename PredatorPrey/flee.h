

#ifndef _flee_h_
#define _flee_h_

#include "ieexec.h"

class CAgent;

class Flee : public IEExec {

public:
    Flee();

    void init   ( CAgent * owner );
    bool start  ();
    bool update ();
    bool finish ();

    CAgent * getOwner ();

    const char * getName();

    enum FleeStates
    {
        Go
    };

private:
    std::string m_name;
    CAgent * m_owner;
	TVirtTime m_dirTick;
	TVirtTime m_minDirTick;
	void newDirection(TVirtTime minTick);

};

#endif
