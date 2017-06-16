
#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
class CStateBase;

class CCharacterFSM
{

private:

public:
		
	CCharacterFSM() {}

	//FSM
	void ChangeState(CStateBase* state);
	void PushState(CStateBase* state);
	void PopState();
	CStateBase* getCurrentState() const;

	void Update();

	void Init();

	void Cleanup();

protected:

	// the stack of states
	std::vector<CStateBase*> states;

	float m_fDeadTimer;
		
};

#endif
