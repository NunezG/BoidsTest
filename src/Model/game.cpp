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
#include "prey.h"
#include "predator.h"
#include "Model\game.h"
#include "Model\GameObjects\ObjectManager.h"

#include "Viewmodel\GameStatesManager.h"

//#include "agent.h"
//#include "virtualtime.h"


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



	if (getDesiredFramesDone(now, s_fps) > getRenderedSinceSecond()) {
		m_periodTimer.startPeriod(PERIOD_RENDER);
		//printf("NEW FRAME!!!");
		newFrame();
		CGameStatesManager::buildFrameConstant();
		//renderFrame();

		if (!(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			CD2DHelper::m_pRenderTarget->BeginDraw();

			CGameStatesManager::Draw(CD2DHelper::m_pRenderTarget);

			renderFrame();

			CD2DHelper::m_pRenderTarget->EndDraw();
		}

		m_periodTimer.startPeriod(PERIOD_IDLE);
	}


	if (getDesiredFramesDone(now, s_bps) > getBuiltSinceSecond()) {
		//	printf("NEW BUILD!!!");

		m_periodTimer.startPeriod(PERIOD_BUILD);
		newBuild();
		CGameStatesManager::buildFramePeriodic();

		CGameStatesManager::Update();


		m_periodTimer.startPeriod(PERIOD_IDLE);
	}

	updateFPS(now);


	//	newFrame();
	//	CObjectManager::buildFrameConstant();


}