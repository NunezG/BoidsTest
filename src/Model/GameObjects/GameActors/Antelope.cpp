#include "Model\GameObjects\GameActors\Antelope.h"
#include "Model\GameObjects\GameActors\ActorFSM\FlagSeekState.h"


///////////////////////////////////////////////////////////////////
// CPredator::CPredator
///////////////////////////////////////////////////////////////////
CAntelope::CAntelope(CFlagStand* TeamStand, CFlag* enemyFlag) : CAgent(TeamStand, enemyFlag)  {
	initialize(TeamStand->getPosition());

	m_enemiesToDie = 1;

	m_sight = 100.0f;
	m_attackZone = 100.0f;
	m_killZone = 30.0f;
	m_respawnSeconds =10;
	setMaxSpeed(10.0f);
	//m_sight = 0.2f;
	//m_walkSpeed = 0.15f;
	
	//m_sight = 0.25f;
	//m_walkSpeed = 0.08f;
	SetTeam(ETeam::antelopesTeam);



	m_separationRadius = 40;
	m_cohesionRadius = 100;
	m_alignmentRadius = 1;
	m_separationForce = 500.f;
	m_cohesionForce = 100.f;
	m_alignmentForce = 10.f;
}
