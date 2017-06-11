#include "GameObjects\GameActors\Characters\Character.h"

#include "GameObjects\Flag.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\characterState.h"
#include "GameObjects\GameActors\Characters\Boid.h"
#include "GameObjects\GameActors\Characters\CharacterFSM\Brain.h"





CCharacter::CCharacter(CFlagStand* TeamStand) : CGameObject(TeamStand->GetLocation(), TeamStand->GetTeam())
{
	m_pFlagStand = TeamStand;

};

CCharacter::CCharacter() {

	// Tell the brain to start looking for the leaf.
	//	brain->pushState(findLeaf);

}


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



void CCharacter::Update()
{
	if (!m_bAlive)
	{
		if (m_bAlive) return;

		respawnTimer--;

		if (respawnTimer <= 0)
			Spawn();
	}
	//framesLeft_--;

	//m_fCurrentLocation.X += m_fVelocity->X;
	//m_fCurrentLocation.Y += m_fVelocity->Y;

	// Update the brain. It will run the current state function.
//	brain->update();

	// Update the steering behaviors
//	boid->update();
}



void CCharacter::Spawn()
{

	float randomX = (float)(rand() % (RANDOM_SPAWN * 2 + 1) - RANDOM_SPAWN);
	float randomY = (float)(rand() % (RANDOM_SPAWN * 2 + 1) - RANDOM_SPAWN);

	respawnTimer = 0;
	
	m_fCurrentLocation.X = m_pFlagStand->GetLocation().X + randomX;
	m_fCurrentLocation.Y = m_pFlagStand->GetLocation().Y + randomY;

	//Init(m_pFlagStand->GetLocation().X + randomX, m_pFlagStand->GetLocation().Y + randomY);
	m_bAlive = true;

}


void CCharacter::Die()
{
	LooseFlag();
	m_bAlive = false;
	respawnTimer = RESPAWN_SECONDS;
}