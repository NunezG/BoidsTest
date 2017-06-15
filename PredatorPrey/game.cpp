////////////////////////////////////////////////////////////////////////////////
// file: game.cpp
// author: Radim Rehurek
// last update: 25.09.04
//
// game is an independent simulation unit, has its own virtual time, world, agents
//////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <cstdlib>

#include "virtualtime.h"
#include "prey.h"
#include "predator.h"
#include "game.h"
#include "gameManager.h"
#include "GameObjects\ObjectManager.h"
#include "GameObjects\GameActors\Characters\Antelope.h"
#include "GameObjects\GameActors\Characters\Lion.h"

CGame * g_game;

///////////////////////////////////////////////////////////////////
// CGame::CGame
// initialize everything (timers, speeds) to zero
///////////////////////////////////////////////////////////////////
CGame::CGame(int granularity, int preyNum, int predatorNum) {
	m_time = new CVirtualTime();
	//m_world = new CWorld(granularity);
	srand((unsigned int)(m_time->timeNow())); // first world ^ is always identical
/*
	for (int i = 0; i < preyNum; i++)
		registerAgent(new CPrey());
	for (int i = 0; i < predatorNum; i++)
		registerAgent(new CPredator());
*/
	m_framesBuiltPS = m_framesRenderedPS = 0;
	m_lastFramesRendered = m_framesRendered = 0;
	m_lastFramesBuilt = m_framesBuilt = 0;
	m_periodTimer.initialize(m_time);
	m_lastSec = m_time->timeNow();
}

///////////////////////////////////////////////////////////////////
// CGame::~CGame
// destroys all registered agents as well
///////////////////////////////////////////////////////////////////
CGame::~CGame() {

	delete m_world;
	delete m_time;
}


///////////////////////////////////////////////////////////////////
// CGame::buildFramePeriodic
// do some not-so-urgent work
///////////////////////////////////////////////////////////////////
int CGame::buildFramePeriodic() {
	CObjectManager::updateAI(0.0f);
	return 0;
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


///////////////////////////////////////////////////////////////////
// CGame::registerAgent
// register agent for the simulation
///////////////////////////////////////////////////////////////////
int CGame::registerAgent(ETeam team) {

	if (team == antelopesTeam)
	{
		
		m_agents.push_back(new CAntelope(&g_game->stands[0], g_game->m_pFlags[1]));
	}
	else
	{

		m_agents.push_back(new CLion(&g_game->stands[1], g_game->m_pFlags[0]));

	}

	//static_cast<CAgent&>(m_agents.back()).initialize(TeamStand->getPosition());
	return 0;
}