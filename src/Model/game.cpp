////////////////////////////////////////////////////////////////////////////////
// file: game.cpp
// author: Radim Rehurek
// last update: 25.09.04
//
// game is an independent simulation unit, has its own virtual time, world, agents
//////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <cstdlib>

#include "Model\virtualtime.h"
#include "Model\game.h"
#include "Model\GameObjects\GameActors\Antelope.h"
#include "Model\GameObjects\GameActors\Lion.h"

#include "Viewmodel\GameStatesManager.h"

//#include "agent.h"
//#include "virtualtime.h"


CGame * g_game;

///////////////////////////////////////////////////////////////////
// CGame::CGame
// initialize everything (timers, speeds) to zero
///////////////////////////////////////////////////////////////////
CGame::CGame() : gammeFinished(false) 
{
	counter[0] = 0;
	counter[1] = 0;

	m_time = new CVirtualTime();
	//m_world = new CWorld(granularity);
	srand((unsigned int)(m_time->timeNow())); // first world ^ is always identical

	m_framesBuiltPS = m_framesRenderedPS = 0;
	m_lastFramesRendered = m_framesRendered = 0;
	m_lastFramesBuilt = m_framesBuilt = 0;
	m_periodTimer.initialize(m_time);
	m_lastSec = m_time->timeNow();

	int flags = 0;
	

	stands[0] = CFlagStand(Vector2d(120.0f, 130.0f), antelopesTeam);
	stands[1] = CFlagStand(Vector2d(600.0f, 160.0f), lionsTeam);

	//initialize flag
	m_pFlags[0] = new CFlag(antelopesTeam, &stands[1], &stands[0]);

	m_pFlags[1] = new CFlag(lionsTeam, &stands[0], &stands[1]);

	// Each particle points to the next.
	int i;
	for (i = 0; i < ANTELOPES_NUMBER; i++)
	{
		printf("Add antelope \n");


		registerAgent(ETeam::antelopesTeam);


		//	m_oCharacters[i] = new CCharacterFSM(stands[0], m_pFlags[1]);

	}

	for (; i < POOL_NUMBER; i++)
	{
		printf("Add lion \n");

		registerAgent(ETeam::lionsTeam);

	}

}

///////////////////////////////////////////////////////////////////
// CGame::~CGame
// destroys all registered agents as well
///////////////////////////////////////////////////////////////////
CGame::~CGame() {

	for (std::list <CAgent *>::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++)
		delete (*agent);
	m_agents.clear();

	delete m_time;
}




///////////////////////////////////////////////////////////////////
// CGame::updateFPS
// update framerate statistics
///////////////////////////////////////////////////////////////////
int CGame::updateFPS(TRealTime now) {
	if (now - m_lastSec > 1.0f) {
		TRealTime elapsed = (TRealTime)1.0;//now - m_lastSec;
		m_framesRenderedPS = (float)(getRenderedSinceSecond() / elapsed);
		m_framesBuiltPS = (float)(getBuiltSinceSecond() / elapsed);
		m_lastFramesBuilt = m_framesBuilt;
		m_lastFramesRendered = m_framesRendered;
		m_lastSec = now;
		m_periodTimer.resetPeriods();
	}
	return 0;
}



void CGame::Tick()
{

	TRealTime now = m_time->timeNow();

	if (getDesiredFramesDone(now, s_bps) > getBuiltSinceSecond()) {
		//	printf("NEW BUILD!!!");

		m_periodTimer.startPeriod(PERIOD_BUILD);
		newBuild();



		for (std::list <CAgent*>::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++) {
			CAgent *_agent = (*agent);

			if (_agent->m_active)
			{
				_agent->processAgentPeriodic();

				if (CheckIfDead(_agent))
				{
					//nearEnemy->ReceiveFlag(character->getFlag());

					_agent->Die();

				}

			}else 
				(_agent)->Update();


				
		}

		


	//	CGameStatesManager::Update();
	}

	updateFPS(now);

	//	g_game->Update();


	if (m_pFlags[0]->pointRule())
	{
		counter[0]++;
		m_pFlags[0]->setOwner(&stands[1]);
		printf("Antelopes COUNTER: \n");

		//printf((char*)counter[0]);

		//printf(" \n");
	}

	if (m_pFlags[1]->pointRule())
	{

		counter[1]++;
		m_pFlags[1]->setOwner(&stands[0]);
		printf("Lions COUNTER: \n");
		//printf((char*)counter[0]);
		//printf(" \n");
	}



	//This manager will check for flag ownership




	//End Game rule
	if (counter[0] >= 5 || counter[1] >= 5)
	{
		gammeFinished = true;

	}



}



bool CGame::CheckIfDead(CAgent* character)
{
	bool canKill = false;
	
	CAgent* nearEnemy;

	for (std::list <CAgent*>::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++) {
		CAgent *_agent = (*agent);

		if (_agent->m_active &&_agent->GetTeam() != character->GetTeam())
		{

		//	float deltaX = (character->getPosX() - _agent->getPosX());
		//	float deltaY = (character->getPosY() - _agent->getPosY());


		//	double distance = sqrt((deltaX * deltaX) - (deltaY * deltaY));

			if (_agent->canKill(character)) {
				

				canKill = true;
				nearEnemy = _agent;
			}
		}

	}

	if (character->IsOfTeam(ETeam::lionsTeam) && canKill)
	{
		if (m_pFlags[1]->getOwner() == character)
		{
			//drop flag
			m_pFlags[1]->setOwner(nearEnemy);

		}


		return true;

	}

	else if (character->IsOfTeam(ETeam::antelopesTeam) && canKill)
	{
		if (m_pFlags[0]->getOwner() == character)
		{
			//drop flag
			m_pFlags[0]->setOwner(nearEnemy);
		}

		return true;
	}

	return canKill;

}




///////////////////////////////////////////////////////////////////
// CGame::registerAgent
// register agent for the simulation
///////////////////////////////////////////////////////////////////
int CGame::registerAgent(ETeam team) {

	if (team == antelopesTeam)
	{

		m_agents.push_back(new CAntelope(&stands[0], m_pFlags[0]));
	}
	else
	{

		m_agents.push_back(new CLion(&stands[1], m_pFlags[1]));

	}

	//static_cast<CAgent&>(m_agents.back()).initialize(TeamStand->getPosition());
	return 0;
}

