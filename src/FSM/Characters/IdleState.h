
#ifndef IDLESTATE_H
#define IDLESTATE_H

//#include "SDL.h"
#include "characterState.h"

class CIdleState : public CCharacterState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void Update();
	//void Draw(ID2D1HwndRenderTarget* renderTarget);

	static CIdleState* Instance() {
		return &m_IdleState;
	}

protected:
	CIdleState() { }

private:
	static CIdleState m_IdleState;

};

#endif