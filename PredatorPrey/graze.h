
#ifndef _graze_h_
#define _graze_h_

#include "ieexec.h"

class CPrey;

class Graze : public IEExec {
public:
    Graze();
    void init   ( CAgent * owner );
    bool start  ();
    bool update ();
    bool finish ();
    CAgent * getOwner ();
    const char * getName();
    enum GrazeStates { Go };

private:
    std::string m_name;
    CPrey * m_owner;
};

#endif
