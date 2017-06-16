#include "gameStart.h"
#include "Viewmodel\GameStatesManager.h"
#include "Viewmodel\introstate.h"
#include "Model\game.h"


int s_fps = 50; // desired initial frame rate
int s_bps = 20; // desired initial build rate

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
		}
		else
		{			
			CGameStatesManager::Update();
		}
	}

	// cleanup the engine
	CGameStatesManager::Cleanup();
}

bool Init()
{
	DemoApp* myApplication = new DemoApp();

	myApplication->Initialize(WndProc);

	m_running = true;

	CGameStatesManager::ChangeState(CIntroState::Instance());

	return true;

}


int pascal WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR, int cmdShow) {

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		// initialize the test		
		if (Init())
		{

			RunMessageLoop();

		}

		CoUninitialize();

		delete g_game;

	}

	return 0;
}


