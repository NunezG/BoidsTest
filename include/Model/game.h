#ifndef _game_h_
#define _game_h_

#include <list>
#include <assert.h>
#include "virtualtime.h"
#include "GameObjects\GameActors\StartPosition.h"
#include "GameObjects\Flag.h"

//class CWorld;
class CVirtualTime;
class CAgent;
class CGame;

extern CGame *g_game;

#define M_PIf 3.14159265358979323846f

extern float randf();
extern int rand(int max);

extern int s_fps; // desired frame rate
extern int s_bps; // desired build rate
const int WIN_CONDITION = 5;

class CGame {
protected:
	// the stack of states

	TRealTime m_lastSec;
	unsigned int m_lastFramesRendered;
	unsigned int m_lastFramesBuilt;
	unsigned int m_framesBuilt;
	unsigned int m_framesRendered;
public:
	float m_framesBuiltPS;
	float m_framesRenderedPS;
	//CTimer m_periodTimer;
	CVirtualTime *m_time;

	CGame(int lions, int antelopes);
	~CGame();
	void newFrame() { m_time->newFrame(); m_framesRendered++; }
	void newBuild() { m_framesBuilt++; }
	TRealTime getTimeElapsedSinceSecond(TRealTime now) const { return now - m_lastSec; }
	unsigned int getBuiltSinceSecond() const { return m_framesBuilt - m_lastFramesBuilt; }

	unsigned int getRenderedSinceSecond() const { return m_framesRendered - m_lastFramesRendered; }
	unsigned int getDesiredFramesDone(TRealTime now, unsigned int fps) const { return (unsigned int)(getTimeElapsedSinceSecond(now) * fps); }

	//int buildFrame();
	int updateFPS(TRealTime now);

	void Tick();

	
	int counter[2];


	//void Init();

//	void Cleanup();
//	void Update();


	bool CheckIfDead(CAgent* character);

//	int updateAI(TRealTime maxTime);


	std::list <CAgent* > m_agents;
	CFlagStand stands[2];
	CFlag* m_pFlags[2];

	int registerAgent(ETeam team);

	bool gammeFinished;


};

#endif
