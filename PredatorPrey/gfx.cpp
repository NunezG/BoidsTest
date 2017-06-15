////////////////////////////////////////////////////////////////////////////////
// file: gfx.cpp
// author: Radim Rehurek
// last update: 29.09.04
//
// anything to do with graphics goes here
//////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdarg>

#include "game.h"
#include "prey.h"
#include "predator.h"
#include "gameManager.h"
#include "GameObjects\ObjectManager.h"
#include "Renderer\D2DHelper.h"



const float PREDATOR_SIZE = 0.005f; // predator size (in world units)
const float PREY_SIZE = 0.003f; // prey size

RECT clRect = {150, 50, 850, 850}; // initial window screen coordinates

int PREDATOR_GLLIST;
int PREY_GLLIST;




///////////////////////////////////////////////////////////////////
// CPredator::drawAgent
// draws a sphere as compiled gl list
///////////////////////////////////////////////////////////////////
void CPredator::drawAgent() const {

}

///////////////////////////////////////////////////////////////////
// CPrey::drawAgent
// draws a sphere as compiled gl list
///////////////////////////////////////////////////////////////////
void CPrey::drawAgent() const {
   


}



void printText(int x, int y, char *format, ...) {
    va_list va;
    char buf[256];
    va_start(va, format);
    vsprintf(buf, format, va);
    va_end(va);

	//std::string ss = buf;
//	std::wstring sfsf = ss.c_str();

    CD2DHelper::outText(x, y, buf);
}

///////////////////////////////////////////////////////////////////
// CGame::renderFrame
// draw the world, draw the agents. also prints some stats
///////////////////////////////////////////////////////////////////
void CGame::renderFrame() {
   
//	CD2DHelper::m_pRenderTarget->BeginDraw();
    //printText(10, 40, "%.4g fps / %.4g fps", m_framesRenderedPS, m_framesBuiltPS);
    printText(-50, -60, "Rendered : %.1f fps (load %.0f%%)", m_framesRenderedPS, 100 * m_periodTimer.getTimeSpent(PERIOD_RENDER));
    printText(-50, 0, "Built : %.1f fps (load %.0f%%)", m_framesBuiltPS, 100 * m_periodTimer.getTimeSpent(PERIOD_BUILD));
  //  if (100 * m_periodTimer.getTimeSpent(PERIOD_IDLE) < 10)
    //    glColor3f(1.0f, 0.2f, 0.2f);
    printText(-50, 60, "Idle (load %.0f%%)", 100 * m_periodTimer.getTimeSpent(PERIOD_IDLE));
 //   glColor3f(0.3f, 0.4f, 0.5f);
    printText(-50, 120, "desired %d fps / %d bps", s_fps, s_bps);
    printText(-50, 180, "simulation speed %.2f / time %.3f", m_time->getSpeed(), m_time->tickNow());
	
    printText(10, 240, (char *)(g_game->m_time->getHWCounterPresent() ? "hw counter" : "sw counter"));
 //   glEnable(GL_LIGHTING);

//	printText(200, 200, "TEEEESSSSSSSS");
//	CD2DHelper::outText(150, 150, "TEEEESSSSSSSS");


//	CD2DHelper::m_pRenderTarget->EndDraw();

       //     glLoadIdentity();


	for (std::list <CAgent *>::iterator agent = g_game->m_agents.begin(); agent != g_game->m_agents.end(); agent++) {
		((*agent))->drawAgent();
		((*agent))->m_marked = false;

		//m_world->drawWorld();

	}
}

///////////////////////////////////////////////////////////////////
// setMaterial
// specify material parameters
///////////////////////////////////////////////////////////////////
void setMaterial(float spec[], float amb[], float diff[], float shin[])
{
 // glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  //glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  //glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  //glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}


