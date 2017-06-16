#include "Model\GameActors\Lion.h"

CLion::CLion(CFlagStand* flagStand, CFlag* enemyFlag) : 
	CAgent(flagStand, enemyFlag)
{
	initialize(flagStand->getPosition());
	m_enemiesToDie = 4;

	m_respawnSeconds = 20;
	m_sight = 100.0f;
	m_attackZone = 200.0f;
	m_killZone = 10.0f;

	setMaxSpeed(7.0f);

	SetTeam(ETeam::lionsTeam);


	m_separationRadius = 600;
	m_cohesionRadius = 0;
	m_alignmentRadius = 100;
	m_separationForce = 100.f;
	m_cohesionForce = 0.f;
	m_alignmentForce = 0.1f;
}
