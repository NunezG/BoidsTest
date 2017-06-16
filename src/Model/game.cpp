#include <list>
#include <cstdlib>
#include "Model\virtualtime.h"
#include "Model\game.h"
#include "Model\GameActors\antelope.h"
#include "Model\GameActors\lion.h"
#include "Viewmodel\gameStatesManager.h"

CGame * g_game;

CGame::CGame(int lions, int antelopes) : gammeFinished(false) 
{
	counter[0] = 0;
	counter[1] = 0;

	m_time = new CVirtualTime();

	srand((unsigned int)(m_time->timeNow()));

	m_framesBuiltPS = m_framesRenderedPS = 0;
	m_lastFramesRendered = m_framesRendered = 0;
	m_lastFramesBuilt = m_framesBuilt = 0;
	m_lastSec = m_time->timeNow();	

	//Initialize stands
	stands[0] = CFlagStand(Vector2d(160.0f, 180.0f), antelopesTeam);
	stands[1] = CFlagStand(Vector2d(760.0f, 600.0f), lionsTeam);

	//initialize flag
	m_pFlags[0] = new CFlag(antelopesTeam, &stands[1], &stands[0]);

	m_pFlags[1] = new CFlag(lionsTeam, &stands[0], &stands[1]);

	// Initialize agents
	for (int i = 0; i < antelopes; ++i)
		registerAgent(ETeam::antelopesTeam);
	

	for (int i = 0; i < lions; ++i)	
		registerAgent(ETeam::lionsTeam);
}

CGame::~CGame() {

	for (std::list <CAgent *>::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++)
		delete (*agent);
	m_agents.clear();

	delete m_time;
}


int CGame::updateFPS(TRealTime now) {
	if (now - m_lastSec > 1.0f) {
		TRealTime elapsed = (TRealTime)1.0;//now - m_lastSec;
		m_framesRenderedPS = (float)(getRenderedSinceSecond() / elapsed);
		m_framesBuiltPS = (float)(getBuiltSinceSecond() / elapsed);
		m_lastFramesBuilt = m_framesBuilt;
		m_lastFramesRendered = m_framesRendered;
		m_lastSec = now;
	}
	return 0;
}


void CGame::Tick()
{
	TRealTime now = m_time->timeNow();

	//Fixed builds per second
	if (getDesiredFramesDone(now, s_bps) > getBuiltSinceSecond())
	{
		newBuild();

		for (std::list <CAgent*>::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++) {
			CAgent *_agent = (*agent);

			_agent->Update();

			//Get flag from stand
			if (_agent->m_active && _agent->m_TargetFlag->getOwner()->objectType() == EObjectType::Stand
				&& (_agent->m_TargetFlag->getOwner()->getPosition() - _agent->getPosition()).length() < 50)
			{
				_agent->m_TargetFlag->setOwner(_agent);

			}
		}
	}

	updateFPS(now);

	//Scoring point rule
	if (m_pFlags[0]->pointRule())
	{
		counter[0]++;
		m_pFlags[0]->setOwner(&stands[1]);
	}

	if (m_pFlags[1]->pointRule())
	{
		counter[1]++;
		m_pFlags[1]->setOwner(&stands[0]);
	}

	//End Game rule
	if (counter[0] >= WIN_CONDITION || counter[1] >= WIN_CONDITION)
	{
		gammeFinished = true;

	}
}


int CGame::registerAgent(ETeam team) {

	if (team == antelopesTeam)
		m_agents.push_back(new CAntelope(&stands[0], m_pFlags[0]));
	else
		m_agents.push_back(new CLion(&stands[1], m_pFlags[1]));

	return 0;
}

