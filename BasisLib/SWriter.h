#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <vector>
#include <string>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

struct TextData
{
	std::wstring text;
	D2D1_RECT_F layout;
	D2D1::ColorF color = { 0.0f, 0.0f, 0.0f, 1.0f };
};

class SWriter
{
	std::vector<TextData> m_TextList;
public:
	void AddText(std::wstring text,
			 	 float x, float y,
			 	 D2D1::ColorF color = { 0.0f, 0.0f, 0.0f, 1.0f });
public:
	ID2D1Factory* m_pD2DFactory = nullptr;
	IDWriteFactory* m_pDWriteFactory = nullptr;
	IDWriteTextFormat* m_pDefaultTextFormat = nullptr;
	ID2D1RenderTarget* m_pRT = nullptr;
	ID2D1SolidColorBrush* m_pDefaultBrush = nullptr;
public:
	bool Create(IDXGISurface1* pBackBuffer);
	bool Init();
	bool Frame();
	bool PreRender();
	bool Render();
	bool PostRender();
	bool Release();
	bool CreateDXWriteRT(IDXGISurface1* pSurface);

	static SWriter& GetInstance()
	{
		static SWriter input;
		return input;
	}
private:
	SWriter() {}
};

#define I_Writer SWriter::GetInstance()
