

#ifndef _Chase_H_
#define _Chase_H_

#include "ieexec.h"

class Character;

class Chase : public IEExec {
public:
	Chase();
	void init   ( CAgent * owner );
	bool start  ();
	bool update ();
	bool finish ();

	CAgent * getOwner ();
	const char * getName();
	enum ChaseStates {
		Go
	};

	void newDirection ();

private:
	std::string m_name;
	CAgent * m_owner;
};

#endif
