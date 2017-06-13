#ifndef _game_h_
#define _game_h_

#include <list>
#include <assert.h>
#include "gameManager.h"
#include "virtualtime.h"

class CWorld;
class CVirtualTime;
class CAgent;
class CGame;

extern CGame *g_game;

class CTimer {
private:
	EPeriod m_currentPeriod;
	TRealTime m_currentStart;
	TRealTime m_timers[PERIOD_NUM];
	TRealTime m_lastTimers[PERIOD_NUM];
	CVirtualTime * m_virtualTime;
public:
	void initialize(CVirtualTime * vtimer) {
		m_virtualTime = vtimer;
		m_currentPeriod = PERIOD_IDLE;
		resetPeriods();
		for (int i = 0; i < PERIOD_NUM; i++)
			m_lastTimers[i] = 0.0;
	}
	void startPeriod(EPeriod newPeriod) {
		TRealTime timeNow = m_virtualTime->timeNow();
		TRealTime elapsed = timeNow - m_currentStart;
		m_timers[m_currentPeriod] += elapsed;
		m_currentStart = timeNow;
		m_currentPeriod = newPeriod;
	}
	TRealTime getTimeSpent(EPeriod period) const {
		assert(period >= 0 && period < PERIOD_NUM);
		return m_lastTimers[period];
	}
	void resetPeriod(EPeriod period) {
		m_lastTimers[period] = m_timers[period];
		m_timers[period] = 0.0;
	}
	void resetPeriods() {
		startPeriod(PERIOD_IDLE);
		for (int i = 0; i < PERIOD_NUM; i++)
			resetPeriod((EPeriod)i);
	}
};

class CGame {
protected:
	TRealTime m_lastSec;
	unsigned int m_lastFramesRendered;
	unsigned int m_lastFramesBuilt;
	unsigned int m_framesBuilt;
	unsigned int m_framesRendered;
public:
	float m_framesBuiltPS;
	float m_framesRenderedPS;
	CTimer m_periodTimer;
	CVirtualTime *m_time;
	CWorld *m_world;

	CGame(int granularity, int preyNum, int predatorNum);
	~CGame();
	int buildFramePeriodic();
	void newFrame() { m_time->newFrame(); m_framesRendered++; }
	void newBuild() { m_framesBuilt++; }
	TRealTime getTimeElapsedSinceSecond(TRealTime now) const { return now - m_lastSec; }
	unsigned int getRenderedSinceSecond() const { return m_framesRendered - m_lastFramesRendered; }
	unsigned int getBuiltSinceSecond() const { return m_framesBuilt - m_lastFramesBuilt; }
	unsigned int getDesiredFramesDone(TRealTime now, unsigned int fps) const { return (unsigned int)(getTimeElapsedSinceSecond(now) * fps); }

	void renderFrame(); // defined in gfx.cpp
	int buildFrame();
	int updateFPS(TRealTime now);
};

#endif
