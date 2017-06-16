#include "Model\GameObjects\GameActors\Antelope.h"


///////////////////////////////////////////////////////////////////
// CPredator::CPredator
///////////////////////////////////////////////////////////////////
CAntelope::CAntelope(CFlagStand* TeamStand, CFlag* enemyFlag) : CAgent(TeamStand, enemyFlag)  {
	initialize(TeamStand->getPosition());

	m_enemiesToDie = 1;

	m_sight = 50.0f;
	m_attackZone = 20.0f;
	m_respawnSeconds =1;
	setMaxSpeed(10.0f);
	//m_sight = 0.2f;
	//m_walkSpeed = 0.15f;
	
	//m_sight = 0.25f;
	//m_walkSpeed = 0.08f;
	SetTeam(ETeam::antelopesTeam);
}

int CAntelope::processAgentConstant()
{

	return 0;



}



int CAntelope::processAgentPeriodic()
{


	return 0;


}
