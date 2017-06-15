
//#include <stdio.h>

#include "Model\GameObjects\ObjectManager.h"
#include "Model\GameObjects\GameActors\Character.h"
#include "Model\game.h"
#include "Model\GameObjects\GameActors\agent.h"

#include <cassert>
#include "Model\GameObjects\GameActors\Antelope.h"
#include "Model\GameObjects\GameActors\Lion.h"
//int CObjectManager::POOL_SIZE;

//CCharacterFSM CObjectManager::m_aCharacters[LIONS_NUMBER + ANTELOPES_NUMBER];
//CCharacterFSM* CObjectManager::m_pFirstDeadCharacter;
//CCharacterFSM* CObjectManager::m_oCharacters[POOL_NUMBER];

//CFlagStand CObjectManager:: stands[2];
//CFlag* CObjectManager::m_pFlags[2];

CObjectManager *g_model;

///////////////////////////////////////////////////////////////////

//vector<CGameState*> CObjectManager::states;
//bool CObjectManager::m_running;
//bool CObjectManager::m_fullscreen;

void CObjectManager::Init()
{
	printf("CObjectManager Init\n");

	//POOL_SIZE = LIONS_NUMBER + ANTELOPES_NUMBER;
	int flags = 0;
	// initialize SDL
//	SDL_Init(SDL_INIT_VIDEO);

	stands[0] = CFlagStand(Vector2d(120.0f, 130.0f), antelopesTeam);
	stands[1] = CFlagStand(Vector2d(600.0f, 160.0f), lionsTeam);

	//initialize flag
	m_pFlags[0] = new CFlag(antelopesTeam, &stands[0]);

	m_pFlags[1] = new CFlag(lionsTeam, &stands[1]);

	// set the title bar text
//	SDL_WM_SetCaption(title, title);

//	if ( fullscreen ) {
//		flags = SDL_FULLSCREEN;
//	}

	// create the screen surface
	//screen = SDL_SetVideoMode(width, height, bpp, flags);

	//m_fullscreen = fullscreen;
	//m_running = true;

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


	/*
	// The first one is available.
	m_pFirstDeadCharacter = m_oCharacters[0];

	// Each particle points to the next.
	for (int i = 0; i < POOL_NUMBER - 1; i++)
	{
		m_oCharacters[i]->setNext(m_oCharacters[i + 1]);
	}

	// The last one terminates the list.
	m_oCharacters[POOL_NUMBER - 1]->setNext(nullptr);

	*/
	

	/*for (int i = 0; i < LIONS_NUMBER; i++)
	{
		spawnCharacter(lionsTeam, 200.0f, 170.0f, 0, 0);
	}
	
}

void CObjectManager::Cleanup()
{
	// cleanup the all states
/*	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
*/
	// switch back to windowed mode so other 
	// programs won't get accidentally resized
//	if ( m_fullscreen ) {
	//	screen = SDL_SetVideoMode(640, 480, 0, 0);
	//}

	//printf("CObjectManager Cleanup\n");

	// shutdown SDL
	//SDL_Quit();
}
/*

void CObjectManager::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	// let the state draw the screen
	if (states.size() > 0)
	states.back()->Draw(renderTarget);
}

void CObjectManager::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	if (states.size() > 0 && !states.back()->resourcesCreated)
	states.back()->CreateDeviceResources(renderTarget);

}
*/




//Create flag and stand
void CObjectManager::spawnFixedObject(double x, double y, ETeam team)
{
	//We spawn the stands, and the flags will be automatically set 

	//CFlagStand* newStand = new CFlagStand(team);

	// Make sure the pool isn't full.
	//assert(m_pFirstDeadCharacter != NULL);

	// Remove it from the available list.
//	CCharacterFSM* newCharacter = m_pFirstDeadCharacter;
//	m_pFirstDeadCharacter = newCharacter->getNext();

	//newCharacter->init(x, y, xVel, yVel, lifetime);
}



bool CObjectManager::CheckIfDead(CAgent* character)
{
	int enemiesSurrounding = 0;

	CAgent* nearEnemy;

	for (std::list <CAgent*>::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++) {
		CAgent *_agent = (*agent);

		if (_agent->m_active &&_agent->GetTeam() != character->GetTeam())
		{

			float deltaX = (character->getPosX() - _agent->getPosX());
			float deltaY = (character->getPosY() - _agent->getPosY());


			double distance = sqrt((deltaX * deltaX) - (deltaY * deltaY));

			if (distance < 10) {

				enemiesSurrounding++;

				nearEnemy = _agent;
			}
		}



	}
	
		

	if (enemiesSurrounding >= 3)
	{
		nearEnemy->m_TargetFlag->setOwner(character);
		//nearEnemy->ReceiveFlag(character->getFlag());

		character->Die();

		return true;

	}
		
	return false;
	
}


void CObjectManager::Update()
{
	for (std::list <CAgent* >::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++) {

		CAgent *_agent = (*agent);

	
		if (_agent->m_active)
			CheckIfDead(_agent);


			
		//update  even if dead
		(_agent)->Update();




	//	if ()
	//	{
			// Add this particle to the front of the list.
		//	m_oCharacters[i]->setNext(m_pFirstDeadCharacter);
			//m_pFirstDeadCharacter = m_oCharacters[i];
//}
	}
}


/*
CObjectManager::~CObjectManager() {
	for (std::list <CAgent *>::iterator agent = m_agents.begin(); agent != m_agents.end(); agent++)
		delete (*agent);
	m_agents.clear();
}

*/



///////////////////////////////////////////////////////////////////
// CGame::registerAgent
// register agent for the simulation
///////////////////////////////////////////////////////////////////
int CObjectManager::registerAgent(ETeam team) {

	if (team == antelopesTeam)
	{

		m_agents.push_back(new CAntelope(&stands[0], m_pFlags[1]));
	}
	else
	{

		m_agents.push_back(new CLion(&stands[1], m_pFlags[0]));

	}

	//static_cast<CAgent&>(m_agents.back()).initialize(TeamStand->getPosition());
	return 0;
}
