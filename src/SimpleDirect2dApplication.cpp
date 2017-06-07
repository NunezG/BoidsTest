// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved


#include "SimpleDirect2dApplication.h"
#include "FSM\gameManager.h"
#include "D2DHelper.h"

//
// Initialize members.
//
DemoApp::DemoApp() :
    m_hwnd(NULL),
    //m_pD2DFactory(NULL),
  //  m_pWICFactory(NULL),
    m_pDWriteFactory(NULL),
    m_pRenderTarget(NULL)
  /*  m_pTextFormat(NULL),
    m_pPathGeometry(NULL),
    m_pLinearGradientBrush(NULL),
    m_pBlackBrush(NULL),
    m_pGridPatternBitmapBrush(NULL),
    m_pBitmap(NULL),
    m_pAnotherBitmap(NULL)
	*/
{
}

//
// Release resources.
//
DemoApp::~DemoApp()
{
    //SafeRelease(&m_pD2DFactory);
   // SafeRelease(&m_pWICFactory);
    SafeRelease(&m_pDWriteFactory);
    SafeRelease(&m_pRenderTarget);
   /* SafeRelease(&m_pTextFormat);
    SafeRelease(&m_pPathGeometry);
    SafeRelease(&m_pLinearGradientBrush);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pGridPatternBitmapBrush);
    SafeRelease(&m_pBitmap);
    SafeRelease(&m_pAnotherBitmap);
	*/
}

//
// Creates the application window and initializes
// device-independent resources.
//
HRESULT DemoApp::Initialize()
{
    HRESULT hr;

    // Initialize device-indpendent resources, such
    // as the Direct2D factory.
    hr = CreateDeviceIndependentResources();
    if (SUCCEEDED(hr))
    {
        // Register the window class.
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style         = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc   = DemoApp::WndProc;
        wcex.cbClsExtra    = 0;
        wcex.cbWndExtra    = sizeof(LONG_PTR);
        wcex.hInstance     = HINST_THISCOMPONENT;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName  = NULL;
        wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wcex.lpszClassName = L"D2DDemoApp";

        RegisterClassEx(&wcex);

        // Create the application window.
        //
        // Because the CreateWindow function takes its size in pixels, we
        // obtain the system DPI and use it to scale the window size.
        FLOAT dpiX, dpiY;
		D2DHelper::m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

        // Create the application window.
        m_hwnd = CreateWindow(
            L"D2DDemoApp",
            L"Direct2D Demo Application",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
            );
        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            ShowWindow(m_hwnd, SW_SHOWNORMAL);
            UpdateWindow(m_hwnd);
        }
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
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DHelper::m_pD2DFactory);
    if (SUCCEEDED(hr))
    {
        // Create WIC factory.
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            reinterpret_cast<void **>(&D2DHelper::m_pWICFactory)
            );
    }
    if (SUCCEEDED(hr))
    {
        // Create a DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
            );
    }
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&D2DHelper::m_pTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		D2DHelper::m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		D2DHelper::m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

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

    if (!m_pRenderTarget)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top
            );

        // Create a Direct2D render target.
        hr = D2DHelper::m_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_pRenderTarget
            );
    }

	GameManager::CreateDeviceResources(m_pRenderTarget);

    return hr;
}


//
//  Discard device-specific resources which need to be recreated
//  when a Direct3D device is lost
//
void DemoApp::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
  /*  SafeRelease(&m_pBitmap);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pLinearGradientBrush);
    SafeRelease(&m_pAnotherBitmap);
    SafeRelease(&m_pGridPatternBitmapBrush);
	*/
}

//
// The main window message loop.
//
void DemoApp::RunMessageLoop()
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
	GameManager::Cleanup();
}

void DemoApp::Tick()
{
	GameManager::Update();
	
	OnRender();

	
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

    if (SUCCEEDED(hr) && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
    
        m_pRenderTarget->BeginDraw();

		GameManager::Draw(m_pRenderTarget);

        hr = m_pRenderTarget->EndDraw();

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
    if (m_pRenderTarget)
    {
        D2D1_SIZE_U size;
        size.width = width;
        size.height = height;

        // Note: This method can fail, but it's okay to ignore the
        // error here -- it will be repeated on the next call to
        // EndDraw.
        m_pRenderTarget->Resize(size);
    }
}


//
// The window message handler.
//
LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        DemoApp *pDemoApp = (DemoApp *)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(pDemoApp)
            );

        result = 1;
    }
    else
    {
        DemoApp *pDemoApp = reinterpret_cast<DemoApp *>(static_cast<LONG_PTR>(
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
				GameManager::HandleEvents(message);
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
