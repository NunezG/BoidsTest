
#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H

//#include "SDL.h"
#include "characterState.h"

class CAttackState : public CCharacterState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void Update();
	//void Draw(ID2D1HwndRenderTarget* renderTarget);

	static CAttackState* Instance() {
		return &m_IdleState;
	}

protected:
	CAttackState() { }

private:
	static CAttackState m_IdleState;

};

#endif