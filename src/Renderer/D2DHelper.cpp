#include "Renderer\D2DHelper.h"
#include <wincodec.h>

#include <string>

#include <iostream>
#include <sstream>
#include <cstdint>

 IDWriteTextFormat * CD2DHelper::m_pTextFormat;
 ID2D1Factory * CD2DHelper::m_pD2DFactory;
 IWICImagingFactory *CD2DHelper::m_pWICFactory;
 IDWriteFactory *CD2DHelper::m_pDWriteFactory;
 ID2D1HwndRenderTarget *CD2DHelper::m_pRenderTarget;

#define M_PIf 3.14159265358979323846f


 void CD2DHelper::ShowNum(int num, int size)
 {
	 m_pRenderTarget->BeginDraw();
	 m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	 D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();


	 uint32_t mycharr = (uint32_t)num;

	 //	uint32_t mycharr = (uint32_t)CObjectManager::m_pFlags[0]->getOwner()->initialPosition.m_y;


	 //uint32_t mycharr = 9;

	 std::wostringstream oss;
	 oss << mycharr;

	 std::wstring res = oss.str();

	 //	std::wcout << res.c_str() << std::endl;

	 const wchar_t* ttt = res.c_str();

	 CD2DHelper::outText(150,200, (char*)ttt);


	 m_pRenderTarget->EndDraw();

 }


void CD2DHelper::outText(int x, int y,const char * text)
{


	std::wostringstream oss;
	oss << text;

	std::wstring res = oss.str();


	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();

	/*
	const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(
		i * 10,
		D2D1::Point2F(
			renderTargetSize.width / 2,
			renderTargetSize.height / 2));
	*/

	//wszText_ = L"Hello World using  DirectWrite!";
	UINT32 cTextLength_ = (UINT32)wcslen((wchar_t*)res.c_str());

	const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(x, y);

	m_pRenderTarget->SetTransform(trans);



//static const WCHAR sc_helloWorld[] = L"Hello, World!";
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

	//m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));



/*	const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(
		i * 10,
		D2D1::Point2F(
			renderTargetSize.width / 2,
			renderTargetSize.height / 2));

	*/
	const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(x, y);


	
	const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(
	(angle / M_PIf) * 180.0,
	D2D1::Point2F(
	0,
	0));
	


	m_pRenderTarget->SetTransform(rot * trans);

/*
	renderTarget->
		DrawText(
		sc_helloWorld,
		ARRAYSIZE(sc_helloWorld) - 1,
		CD2DHelper::m_pTextFormat,
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		m_pBlackBrush
	);

	*/

	// Draw two rectangles.
/*	D2D1_RECT_F rectangle1 = D2D1::RectF(
		x - rtSize.width * size /100,
		y + rtSize.width * size / 100,
		x + rtSize.width *  size / 100,
		y- rtSize.width * size / 100);
		*/

	D2D1_RECT_F rectangle1 = D2D1::RectF(
		- rtSize.width / size,
		rtSize.width / size +5,
		rtSize.width /  size,
		- (rtSize.width / size +5));



// Draw a filled rectangle.
		m_pRenderTarget->FillRectangle(&rectangle1, color);


	//	m_pRenderTarget->draw   FillGeometry(&rectangle1, color);
		return rectangle1;
}