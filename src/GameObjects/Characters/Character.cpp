#include "Character.h"

#include "../Flag.h"





void CCharacter::ChangeState(CCharacterState* state)
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CCharacter::PushState(CCharacterState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CCharacter::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}

/*
void CCharacter::findLeaf() {
	// Move the ant towards the leaf.
	velocity = D2D1::Point2F();
		new Vector3D(Game.instance.leaf.x - position.x, Game.instance.leaf.y - position.y);

	if (distance(Game.instance.leaf, this) <= 10) {
		// The ant is extremelly close to the leaf, it's time
		// to go home.
		brain.popState(); // removes "findLeaf" from the stack.
		brain.pushState(goHome); // push "goHome" state, making it the active state.
	}

	if (distance(Game.mouse, this) <= MOUSE_THREAT_RADIUS) {
		// Mouse cursor is threatening us. Let's run away!
		// The "runAway" state is pushed on top of "findLeaf", which means
		// the "findLeaf" state will be active again when "runAway" ends.
		brain.pushState(runAway);
	}
}*/