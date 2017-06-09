#include "gameManager.h"

#include "FSM\Game\GameStatesManager.h"
#include "FSM\Game\playstate.h"

///////////////////////////////////////////////////////////////////

bool GameManager::m_running;
bool GameManager::m_fullscreen;
DemoApp* GameManager::myApplication;
CITWindow* GameManager::TestWindow;


bool GameManager::Init(const char* title, int width, int height, 
						 int bpp, bool fullscreen)
{
	int flags = 0;
	height;
	// initialize SDL
//	SDL_Init(SDL_INIT_VIDEO);

	// set the title bar text
//	SDL_WM_SetCaption(title, title);

//	if ( fullscreen ) {
//		flags = SDL_FULLSCREEN;
//	}

	// create the screen surface
	//screen = SDL_SetVideoMode(width, height, bpp, flags);

	m_fullscreen = fullscreen;
	m_running = true;

	printf("GameManager Init\n");

	TestWindow = new CITWindow();

	myApplication = new DemoApp();

	HRESULT hr = myApplication->Initialize(TestWindow);

	if (SUCCEEDED(TestWindow->CreateGameWindow(WndProc)))
	{
		// load the intro
		CGameStatesManager::ChangeState(CPlayState::Instance());

		return true;
	}

	return false;
}



//
// The window message handler.
//
LRESULT CALLBACK GameManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
void GameManager::RunMessageLoop()
{
	MSG msg = { 0 };


	while (GameManager::Running() && WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Tick();
		}
	}

	// cleanup the engine
	CGameStatesManager::Cleanup();
}

void GameManager::Tick()
{
	CGameStatesManager::Update();

	myApplication->OnRender();

	//TestWindow->OnRender();
}
