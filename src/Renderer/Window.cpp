#include "Renderer\Window.h"
#include "Renderer\D2DHelper.h"
#include "Renderer\D2DRenderer.h"

HRESULT CITWindow::CreateGameWindow(WNDPROC messageReceiver)
{

	
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = messageReceiver;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = L"D2DDemoApp";

		RegisterClassEx(&wcex);

		// Create the application window.
		//
		// Because the CreateWindow function takes its size in pixels, we
		// obtain the system DPI and use it to scale the window size.
		FLOAT dpiX, dpiY;
		CD2DHelper::m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

		// Create the application window.
		m_hwnd = CreateWindow(
			L"D2DDemoApp",
			L"Direct2D Demo Application",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<UINT>(ceil(1024.f * dpiX / 96.f)),
			static_cast<UINT>(ceil(768.f * dpiY / 96.f)),
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
		);
		HRESULT hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
		return hr;
}






void CITWindow::OnResize(
	UINT width,
	UINT height
)
{
	if (CD2DHelper::m_pRenderTarget)
	{
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;

		// Note: This method can fail, but it's okay to ignore the
		// error here -- it will be repeated on the next call to
		// EndDraw.
		CD2DHelper::m_pRenderTarget->Resize(size);
	}


}