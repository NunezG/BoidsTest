// Windows Header Files:
#include <windows.h>
#include "FSM\introstate.h"
#include "FSM\playstate.h"

//
// Provides the entry point to the application.
//
int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
)
{
	// Ignore the return value because we want to continue running even in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			DemoApp app;

			if (SUCCEEDED(app.Initialize()))
			{
				// initialize the engine
				GameManager::Init("Engine Test v1.0");

				// load the intro
				GameManager::ChangeState(CPlayState::Instance());

				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}








	return 0;
}
