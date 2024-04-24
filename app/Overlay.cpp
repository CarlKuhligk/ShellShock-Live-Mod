#include "IncludeHead.h"



extern LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMesg, WPARAM wParam, LPARAM lParam);


RulerOverlayOBJ::RulerOverlayOBJ()
{
    windowClass = { }; // set all vars 0
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = MessageHandler;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    windowClass.hCursor = LoadCursor(NULL, IDC_CROSS);
    windowClass.hbrBackground = backgrundColor; // Translucent Background // Key Red
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = "RulerOverlay";

    // Window
    Position.x = CW_USEDEFAULT;
    Position.y = CW_USEDEFAULT;
    Size.cx = 200;
    Size.cy = 50;

}


void RulerOverlayOBJ::createWindow()
{
    assert(RegisterClass(&windowClass));

    hMainWindow = CreateWindow("RulerOverlay", "WindowTitleSSL", WS_POPUP,
        Position.x, Position.y, Size.cx, Size.cy,
        0, 0, hInstance, 0);

    // Translucent Background
    SetWindowLong(hMainWindow, GWL_EXSTYLE, GetWindowLong(hMainWindow, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hMainWindow, RGB(255, 0, 255), 0, LWA_COLORKEY); // Key Red
    ShowWindow(hMainWindow, SW_SHOW);

    SetForegroundWindow(hMainWindow);

    // GDU+ Inizialisation
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartUpInput, nullptr);

    

}

void RulerOverlayOBJ::update()
{
    RedrawWindow(hMainWindow, 0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
}

void RulerOverlayOBJ::setPosition(int x, int y)
{
    Position.x = x;
    Position.y = y;
    setRectangle();
}

void RulerOverlayOBJ::setSize(int width, int hight)
{
    Size.cx = width;
    Size.cy = hight;
    setRectangle();
}

void RulerOverlayOBJ::setRectangle(POINT position, SIZE size)
{
    Position.x = position.x;
    Position.y = position.y;
    Size.cx = size.cx;
    Size.cy = size.cy;
    setRectangle();
}

void RulerOverlayOBJ::setRectangle(int x, int y, int width, int hight)
{
    Position.x = x;
    Position.y = y;
    Size.cx = width;
    Size.cy = hight;
    setRectangle();
}

void RulerOverlayOBJ::setRectangle()
{
    // Set window Top-Most
    SetWindowPos(hMainWindow, HWND_TOPMOST, Position.x, Position.y, Size.cx, Size.cy, 0);
}


void RulerOverlayOBJ::draw(HDC hdc)
{
    Gdiplus::Graphics panel(hdc);


   /* Gdiplus::Pen red(Gdiplus::Color(255, 255, 0, 0), 0.0f);
    Gdiplus::Pen green(Gdiplus::Color(255, 0, 255, 0), 0.0f);
    Gdiplus::Pen blue(Gdiplus::Color(255, 0, 0, 255), 0.0f);
    Gdiplus::Pen white(Gdiplus::Color(255, 255, 255, 255), 0.0f);

    panel.DrawLine(&white, 0, 0, 200, 200);*/
    
}







