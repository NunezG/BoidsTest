
#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H

//#include "SDL.h"
#include "characterState.h"

class CAttackState : public CCharacterState
{
public:
	void Init(CCharacter* owner);
	void Cleanup();

	void Pause();
	void Resume();

	void Update();
	//void Draw(ID2D1HwndRenderTarget* renderTarget);


	CAttackState() { }

private:

};

#endif