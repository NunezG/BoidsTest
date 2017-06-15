//#include "../gameManager.h"

#ifndef D2DHELPER_H
#define D2DHELPER_H

#include <d2d1helper.h>
#include <wincodec.h>
#include <dwrite.h>


/******************************************************************
*                                                                 *
*  Macros                                                         *
*                                                                 *
******************************************************************/

template<class Interface>
inline void
SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif


#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class CD2DHelper
{
public:
	//
	// Creates a Direct2D bitmap from a resource in the
	// application resource file.
	//
	static IDWriteTextFormat *m_pTextFormat;
	static ID2D1Factory *m_pD2DFactory;
	static IWICImagingFactory *m_pWICFactory;
	static IDWriteFactory *m_pDWriteFactory;
	static ID2D1HwndRenderTarget *m_pRenderTarget;

	static void ShowNum(int num, int size);


	static D2D1_RECT_F Rectange(float size, ID2D1SolidColorBrush* color, float x, float y, float angle = 0);

	static void outText(int x, int y, const char * text);


	//static void Showtext(const wchar_t* textToShow, int size);

private:
	
};


#endif