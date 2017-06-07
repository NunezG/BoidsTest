#include "SimpleDirect2dApplication.h"

class D2DHelper
{
public:
	//
	// Creates a Direct2D bitmap from a resource in the
	// application resource file.
	//
	static IDWriteTextFormat *m_pTextFormat;
	static ID2D1Factory *m_pD2DFactory;
	static IWICImagingFactory *m_pWICFactory;
	

	static HRESULT LoadResourceBitmap(
		ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap **ppBitmap
	);

	//
	// Creates a Direct2D bitmap from the specified
	// file name.
	//
	static HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap **ppBitmap
	);
};

