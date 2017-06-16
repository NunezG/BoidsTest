#include "gameStart.h"

#include "Viewmodel\GameStatesManager.h"
#include "Viewmodel\introstate.h"
//#include <ctime>
//#include <iostream>

#include "Model\game.h"
//#include "agent.h"
//#include "virtualtime.h"

#include <iostream>
#include <string>
#include <sstream>

///////////////////////////////////////////////////////////////////

static bool m_fullscreen;
//double GameManager::m_dDeltaTime;
//double GameManager::m_dStartTime = clock();


int s_fps = 60; // desired initial frame rate
int s_bps = 60; // desired initial build rate

static bool m_running;


///////////////////////////////////////////////////////////////////
// randf
// return a pseudorandom number in the range <0.0f, 1.0f>
///////////////////////////////////////////////////////////////////
float randf() { return 1.0f * rand() / RAND_MAX; }

///////////////////////////////////////////////////////////////////
// rand
// return a pseudorandom number in the range <0, min(maxNum, RAND_MAX)>
///////////////////////////////////////////////////////////////////
int rand(int maxNum) { return rand() % (maxNum + 1); }

//
// The window message handler.
//
static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		CITWindow *pDemoApp = (CITWindow *)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pDemoApp)
		);

		result = 1;
	}
	else
	{
		CITWindow *pDemoApp = reinterpret_cast<CITWindow*>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));

		bool wasHandled = false;

		if (pDemoApp)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pDemoApp->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);
			}
			result = 0;
			wasHandled = true;
			break;
			case WM_DISPLAYCHANGE:

				break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;

			default:
				CGameStatesManager::HandleEvents(message);
				break;
			}

		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}


//
// The main window message loop.
//
void RunMessageLoop()
{
	MSG msg = { 0 };

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	while (m_running && WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);


			/*

				double now = clock();
				m_dDeltaTime = now - m_dStartTime;
				cout <<"LOOSOSOSOSOOLOLOOLO: "<< (m_dDeltaTime / CLOCKS_PER_SEC) << endl;
				m_dStartTime = now;
			*/
		}
		else
		{
			double olddelta = 0;

				//olddelta = m_dDeltaTime;
				//m_dDeltaTime = clock() - olddelta;
				//std::cout <<"CLOCKS_PER_SECCLOCKS_PER_SEC\n: "   << (m_dDeltaTime / CLOCKS_PER_SEC) << std::endl;
			
			CGameStatesManager::Update();
		}
	}

	// cleanup the engine
	CGameStatesManager::Cleanup();
}

void doKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0);
	case '1': s_fps = aminmax(0, s_fps - 1, 1000); break;
	case '2': s_fps = aminmax(0, s_fps + 1, 1000); break;
	case '3': s_bps = aminmax(0, s_bps - 1, 1000); break;
	case '4': s_bps = aminmax(0, s_bps + 1, 1000); break;
	//case '5': s_speed = aminmax(0.0f, s_speed - 0.01f, 1.0f); g_game->m_time->setSpeed(s_speed); break;
	//case '6': s_speed = aminmax(0.0f, s_speed + 0.01f, 1.0f); g_game->m_time->setSpeed(s_speed); break;
	//case '9': delete g_game; g_game = new CGame(50, 1, 0); s_speed = 1.0f; g_game->m_time->setSpeed(s_speed); break;
	//case '0': delete g_game; g_game = new CGame(70 + rand(30), 40 + rand(40), rand(2)); g_game->m_time->setSpeed(s_speed); break;
	}
}



bool Init()
{



	DemoApp* myApplication = new DemoApp();

	HRESULT hr = myApplication->Initialize(WndProc);


	//m_objectManager = new CObjectManager();
	int flags = 0;
	// initialize SDL
	//	SDL_Init(SDL_INIT_VIDEO);

	// set the title bar text
	//	SDL_WM_SetCaption(title, title);

	//	if ( fullscreen ) {
	//		flags = SDL_FULLSCREEN;
	//	}

	// create the screen surface
	//screen = SDL_SetVideoMode(width, height, bpp, flags);

	m_running = true;

	//std::cout.flush();
	// load the intro
	CGameStatesManager::ChangeState(CIntroState::Instance());

	return true;

}





//
// Provides the entry point to the application.
//

int main(int argc, char* argv[]) {
//#endif
	// Ignore the return value because we want to continue running even in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{

		// initialize the test		
		if (Init())
		{
			//NEW FUNCTIONS


			RunMessageLoop();

		}


		CoUninitialize();

		delete g_game; // automatically destroys all registered agents

	}


	return 0;
}


