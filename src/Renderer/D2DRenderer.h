// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved
//


// C RunTime Header Files
#ifndef D2DRENDERER_H
#define D2DRENDERER_H

//#include "Window.h"
#include "D2DHelper.h"
//#include "../gameManager.h"


//#include <d2d1.h>
//#include <stdio.h>
class CITWindow;

/******************************************************************
*                                                                 *
*  DemoApp                                                        *
*                                                                 *
******************************************************************/

class DemoApp
{
public:
    DemoApp();
   // ~DemoApp();

    HRESULT Initialize(CITWindow* window);

	HRESULT OnRender();

	void OnResize(
		UINT width,
		UINT height
	);

private:
    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateDeviceResources();

    void DiscardDeviceResources();

	CITWindow* ownerWindow;
  
private:
   // HWND m_hwnd;


};


#endif