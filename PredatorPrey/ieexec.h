
#ifndef _IEEXEC_H_
#define _IEEXEC_H_

#include <string>

class CAgent;

class IEExec
{
public:

    IEExec();
	virtual ~IEExec() {}

    virtual void init   (CAgent * owner ) = 0;
    virtual bool start  ();
    virtual bool update () = 0;
    virtual bool finish ();
    virtual void reset  ();

    virtual CAgent * getOwner  () = 0;

    virtual const char * getName() = 0;

protected:
    int m_state;

    bool m_done;
};


#endif
