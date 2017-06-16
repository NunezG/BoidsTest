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

#include "D2DHelper.h"

class CITWindow;


class DemoApp
{
public:

    HRESULT Initialize(WNDPROC messageReceiver);

private:
    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateRenderTarget();

	CITWindow* ownerWindow;
  
private:

};


#endif