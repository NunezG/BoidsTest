#ifndef STACKFSM_H
#define STACKFSM_H

#include "Renderer/D2DHelper.h"
#include "stateBase.h"
#include <vector>

//typedef void(*vFunctionCall)(int args);

class StackFSM
{
private:
	std::vector<CStateBase*> stack;

public:

	StackFSM() : stack()
	{
	}

	void update() {
		CStateBase* currentStateFunction = getCurrentState();

		if (currentStateFunction != nullptr) {
			currentStateFunction->Update();
		}
	}

	CStateBase* popState() {
		return stack.back();
		stack.pop_back();
	}

	void pushState(CStateBase* state) {
		if (getCurrentState() != state) {
			stack.push_back(state);
		}
	}

	CStateBase* getCurrentState()
	{
		return stack.size() > 0 ? stack[stack.size() - 1] : nullptr;
	}

	 void Pause(){}
	 void Resume(){}

};

#endif