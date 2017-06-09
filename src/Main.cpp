// Windows Header Files:
#include <windows.h>
#include "gameManager.h"

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
				
		// initialize the test		
		if (GameManager::Init("Ivory Tower Test v1.0")) 
			GameManager::RunMessageLoop();

		CoUninitialize();
	}


	return 0;
}


