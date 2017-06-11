
//#include <stdio.h>

#include "GameObjects\ObjectManager.h"
#include "GameObjects\GameActors\Characters\Character.h"

#include <cassert>

//int CObjectManager::POOL_SIZE;

//CCharacter CObjectManager::m_aCharacters[LIONS_NUMBER + ANTELOPES_NUMBER];
//CCharacter* CObjectManager::m_pFirstDeadCharacter;
CCharacter* CObjectManager::m_oCharacters[POOL_NUMBER];
CFlagStand* CObjectManager:: stands[2];
CFlag* CObjectManager::m_pFlags[2];


///////////////////////////////////////////////////////////////////

//vector<CGameState*> CObjectManager::states;
//bool CObjectManager::m_running;
bool CObjectManager::m_fullscreen;

void CObjectManager::Init()
{
	//POOL_SIZE = LIONS_NUMBER + ANTELOPES_NUMBER;
	int flags = 0;
	// initialize SDL
//	SDL_Init(SDL_INIT_VIDEO);

	stands[0] = new CFlagStand(point2F(120.0f, 130.0f), antelopesTeam);
	stands[1] = new CFlagStand(point2F(500, 160.0f), lionsTeam);

	//initialize flag
	m_pFlags[0] = new CFlag(antelopesTeam, stands[0]);

	m_pFlags[1] = new CFlag(lionsTeam, stands[1]);

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
		 
		m_oCharacters[i] = new CCharacter(stands[0], m_pFlags[1]);
	
		m_oCharacters[i]->Spawn();
	}

	for (; i < POOL_NUMBER; i++)
	{

		m_oCharacters[i] = new CCharacter(stands[1], m_pFlags[0]);

		m_oCharacters[i]->m_TargetFlag = m_pFlags[0];

		m_oCharacters[i]->Spawn();
	}

	printf("CObjectManager Init\n");

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

	printf("CObjectManager Cleanup\n");

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
//	CCharacter* newCharacter = m_pFirstDeadCharacter;
//	m_pFirstDeadCharacter = newCharacter->getNext();

	//newCharacter->init(x, y, xVel, yVel, lifetime);
}



bool CObjectManager::CheckIfDead(static CCharacter* character)
{
	int enemiesSurrounding = 0;

	CCharacter* nearEnemy;

	for (int i = 0; i < POOL_NUMBER; i++)
	{
		 		
		if (m_oCharacters[i]->GetTeam() != character->GetTeam())
		{
			float deltaX = (character->GetLocation().X - m_oCharacters[i]->GetLocation().X);
			float deltaY = (character->GetLocation().Y - m_oCharacters[i]->GetLocation().Y);


			double distance = sqrt((deltaX * deltaX) - (deltaY * deltaY));

			if (distance < 100) {

				enemiesSurrounding++;

				nearEnemy = m_oCharacters[i];
			}
		}

	}

	if (enemiesSurrounding >= 3)
	{
		nearEnemy->ReceiveFlag(character->getFlag());

		character->Die();

		return true;

	}
		
	return false;
	
}


void CObjectManager::Update()
{
	for (int i = 0; i < POOL_NUMBER; i++)
	{
		if (m_oCharacters[i]->isAlive())
			CheckIfDead(m_oCharacters[i]);
			
		m_oCharacters[i]->Update();


	//	if ()
	//	{
			// Add this particle to the front of the list.
		//	m_oCharacters[i]->setNext(m_pFirstDeadCharacter);
			//m_pFirstDeadCharacter = m_oCharacters[i];
//}
	}
}