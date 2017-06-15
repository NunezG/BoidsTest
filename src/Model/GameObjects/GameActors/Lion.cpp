#include "Model\GameObjects\GameActors\Lion.h"


///////////////////////////////////////////////////////////////////
// CPredator::CPredator
///////////////////////////////////////////////////////////////////
CLion::CLion(CFlagStand* TeamStand, CFlag* enemyFlag) : 
	CAgent(TeamStand, enemyFlag)
{
	initialize(TeamStand->getPosition());

	m_sight = 400.0f;
	m_walkSpeed = 0.60f;
	setMaxSpeed(10000.0f);

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

