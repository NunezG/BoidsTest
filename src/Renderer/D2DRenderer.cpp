// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved


#include "Renderer\D2DRenderer.h"

#include "Renderer\Window.h"
#include "Renderer\GameFSM\GameStatesManager.h"


//
// Initialize members.
//
DemoApp::DemoApp()// :
   // m_hwnd(NULL),
    //m_pD2DFactory(NULL),
  //  m_pWICFactory(NULL),
  //  m_pDWriteFactory(NULL),
   // m_pRenderTarget(NULL)
  /*  m_pTextFormat(NULL),
    m_pPathGeometry(NULL),
    m_pLinearGradientBrush(NULL),
    m_pBlackBrush(NULL),
    m_pGridPatternBitmapBrush(NULL),
    m_pBitmap(NULL),
    m_pAnotherBitmap(NULL)
	*/
{
	//ownerWindow = new CITWindow();
}

//
// Release resources.
//
//DemoApp::~DemoApp()
//{
    //SafeRelease(&m_pD2DFactory);
   // SafeRelease(&m_pWICFactory);
  //  SafeRelease(&m_pDWriteFactory);
  //  SafeRelease(&m_pRenderTarget);
   /* SafeRelease(&m_pTextFormat);
    SafeRelease(&m_pPathGeometry);
    SafeRelease(&m_pLinearGradientBrush);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pGridPatternBitmapBrush);
    SafeRelease(&m_pBitmap);
    SafeRelease(&m_pAnotherBitmap);
	*/
//}

//
// Creates the application window and initializes
// device-independent resources.
//
HRESULT DemoApp::Initialize(CITWindow* window)
{
	ownerWindow = window;

    HRESULT hr;

    // Initialize device-indpendent resources, such
    // as the Direct2D factory.
    hr = CreateDeviceIndependentResources();
   
	if (SUCCEEDED(hr))
    {

	//	return CreateGameWindow();
    }

	return hr;
}


//
// Create resources which are not bound
// to any device. Their lifetime effectively extends for the
// duration of the app. These resources include the Direct2D,
// DirectWrite, and WIC factories; and a DirectWrite Text Format object
// (used for identifying particular font characteristics) and
// a Direct2D geometry.
//
HRESULT DemoApp::CreateDeviceIndependentResources()
{
    static const WCHAR msc_fontName[] = L"Verdana";
    static const FLOAT msc_fontSize = 50;
    HRESULT hr;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &CD2DHelper::m_pD2DFactory);
    if (SUCCEEDED(hr))
    {
        // Create WIC factory.
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            reinterpret_cast<void **>(&CD2DHelper::m_pWICFactory)
            );
    }
    if (SUCCEEDED(hr))
    {
        // Create a DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(CD2DHelper::m_pDWriteFactory),
            reinterpret_cast<IUnknown **>(&CD2DHelper::m_pDWriteFactory)
            );
    }
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = CD2DHelper::m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&CD2DHelper::m_pTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		CD2DHelper::m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		CD2DHelper::m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	}

    return hr;
}

//
//  This method creates resources which are bound to a particular
//  Direct3D device. It's all centralized here, in case the resources
//  need to be recreated in case of Direct3D device loss (eg. display
//  change, remoting, removal of video card, etc).
//
HRESULT DemoApp::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (!CD2DHelper::m_pRenderTarget)
    {
        RECT rc;
        GetClientRect(ownerWindow->m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top
            );

        // Create a Direct2D render target.
        hr = CD2DHelper::m_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(ownerWindow->m_hwnd, size),
			&CD2DHelper::m_pRenderTarget
            );
    }

	CGameStatesManager::CreateDeviceResources(CD2DHelper::m_pRenderTarget);

    return hr;
}


//
//  Discard device-specific resources which need to be recreated
//  when a Direct3D device is lost
//
void DemoApp::DiscardDeviceResources()
{
    SafeRelease(&CD2DHelper::m_pRenderTarget);
  /*  SafeRelease(&m_pBitmap);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pLinearGradientBrush);
    SafeRelease(&m_pAnotherBitmap);
    SafeRelease(&m_pGridPatternBitmapBrush);
	*/
}

//
//  Called whenever the application needs to display the client
//  window. This method draws a bitmap a couple times, draws some
//  geometries, and writes "Hello, World"
//
//  Note that this function will not render anything if the window
//  is occluded (e.g. when the screen is locked).
//  Also, this function will automatically discard device-specific
//  resources if the Direct3D device disappears during function
//  invocation, and will recreate the resources the next time it's
//  invoked.
//
HRESULT DemoApp::OnRender()
{
    HRESULT hr;

    hr = CreateDeviceResources();

    if (SUCCEEDED(hr) && !(CD2DHelper::m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
    
		CD2DHelper::m_pRenderTarget->BeginDraw();

		CGameStatesManager::Draw(CD2DHelper::m_pRenderTarget);

        hr = CD2DHelper::m_pRenderTarget->EndDraw();

        if (hr == D2DERR_RECREATE_TARGET)
        {
            hr = S_OK;
            DiscardDeviceResources();
        }
    }

    return hr;
}

//
//  If the application receives a WM_SIZE message, this method
//  resize the render target appropriately.
//
void DemoApp::OnResize(UINT width, UINT height)
{
  
}

