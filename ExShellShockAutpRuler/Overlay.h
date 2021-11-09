#pragma once



class RulerOverlayOBJ
{
public:

	// Variabels
	HINSTANCE hInstance = GetModuleHandle(0);

	HWND hMainWindow;
	WNDCLASS windowClass;
	MSG msg;


	// GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartUpInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::Graphics* graphicsOverlay;
	HBRUSH backgrundColor = CreateSolidBrush(RGB(255, 0, 255)); // TranslucentKey

	// Overlay
	SIZE Size = SIZE();
	POINT Position = POINT();


	// Methodes
	RulerOverlayOBJ();

	void createWindow();
	void update();
	void setPosition(int x, int y);
	void setSize(int width, int hight);
	void setRectangle(POINT position, SIZE size);
	void setRectangle(int x, int y, int width, int hight);
	void setRectangle();

	void draw(HDC hdc);

	void drawLine(std::vector<POINT> points, Gdiplus::Pen pen);
	void drawCirle(POINT position, int radius, Gdiplus::Pen pen);
	void drawRectangle(POINT position, SIZE size, Gdiplus::Pen pen);
	void drawCross(POINT position, Gdiplus::Pen pen);

private:

};