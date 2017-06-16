#include "Model\GameActors\antelope.h"
#include "Model\GameActors\ActorFSM\flagSeekState.h"

CAntelope::CAntelope(CFlagStand* flagStand, CFlag* enemyFlag) : CAgent(flagStand, enemyFlag)  {
	initialize(flagStand->getPosition());

	m_enemiesToDie = 1;

	m_sight = 100.0f;
	m_attackZone = 100.0f;
	m_killZone = 30.0f;
	m_respawnSeconds =10;
	setMaxSpeed(10.0f);

	SetTeam(ETeam::antelopesTeam);

	m_separationRadius = 40;
	m_cohesionRadius = 100;
	m_alignmentRadius = 1;
	m_separationForce = 500.f;
	m_cohesionForce = 100.f;
	m_alignmentForce = 10.f;
}
