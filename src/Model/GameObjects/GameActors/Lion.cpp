#include "Model\GameObjects\GameActors\Lion.h"


///////////////////////////////////////////////////////////////////
// CPredator::CPredator
///////////////////////////////////////////////////////////////////
CLion::CLion(CFlagStand* TeamStand, CFlag* enemyFlag) : 
	CAgent(TeamStand, enemyFlag)
{
	initialize(TeamStand->getPosition());
	m_enemiesToDie = 3;

	m_respawnSeconds = 4;
	m_sight = 50.0f;
	m_attackZone = 10.0f;
	setMaxSpeed(5.0f);

	//m_sight = 0.25f;
	//m_walkSpeed = 0.08f;
	SetTeam(ETeam::lionsTeam);
}

int CLion::processAgentConstant()
{

	return 0;


}



int CLion::processAgentPeriodic()
{


	return 0;


}

