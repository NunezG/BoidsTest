#include "View\D2DHelper.h"
#include <wincodec.h>

#include <string>

#include <iostream>
#include <sstream>
#include <cstdint>
#include	"Model\game.h"
 IDWriteTextFormat * CD2DHelper::m_pTextFormat;
 ID2D1Factory * CD2DHelper::m_pD2DFactory;
 IWICImagingFactory *CD2DHelper::m_pWICFactory;
 IDWriteFactory *CD2DHelper::m_pDWriteFactory;
 ID2D1HwndRenderTarget *CD2DHelper::m_pRenderTarget;

#define M_PIf 3.14159265358979323846f

 void CD2DHelper::outText(int x, int y, const char * text)
 {
	 std::wostringstream oss;
	 oss << text;
	 std::wstring res = oss.str();

	 m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	 D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();

	 UINT32 cTextLength_ = (UINT32)wcslen((wchar_t*)res.c_str());

	 const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation((float)x, (float)y);

	 m_pRenderTarget->SetTransform(trans);

	 ID2D1SolidColorBrush *m_pBlackBrush;

	 HRESULT hr = S_OK;

	 // Create a black brush.
	 hr = m_pRenderTarget->CreateSolidColorBrush(
		 D2D1::ColorF(D2D1::ColorF::Black),
		 &m_pBlackBrush
	 );

	 m_pRenderTarget->DrawText(
		 res.c_str(),
		 cTextLength_,
		 m_pTextFormat,
		 D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		 m_pBlackBrush
	 );

 }

D2D1_RECT_F CD2DHelper::Rectange(float size, ID2D1SolidColorBrush* color, float x, float y, float angle)
{
	D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();
	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());


	const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(x, y);

	const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(
		(float)((angle / M_PIf) * 180.0),
		D2D1::Point2F(
			0,
			0));

	m_pRenderTarget->SetTransform(rot * trans);


	D2D1_RECT_F rectangle1 = D2D1::RectF(
		-rtSize.width / size,
		rtSize.width / size + 5,
		rtSize.width / size,
		-(rtSize.width / size + 5));

	// Draw a filled rectangle.
	m_pRenderTarget->FillRectangle(&rectangle1, color);

	return rectangle1;
}


void CD2DHelper::printText(int x, int y, char *format, ...) {
	va_list va;
	char buf[256];
	va_start(va, format);
	vsprintf_s(buf, format, va);
	va_end(va);

	CD2DHelper::outText(x, y, buf);
}

void CD2DHelper::DebugFrame() {
//	printText(-50, -80, "%.4g fps / %.4g fps", g_game-> m_framesRenderedPS, g_game->m_framesBuiltPS);
//	printText(-50, 180, "simulation speed %.2f / time %.3f", g_game->m_time->getSpeed(), g_game->m_time->tickNow());
}
