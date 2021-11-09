#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <cassert> // assert


LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMesg, WPARAM wParam, LPARAM lParam)
{
	switch (uMesg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMesg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASS window;
	MSG msg;

	window = {}; // set all vars 0
	window.style = CS_HREDRAW | CS_VREDRAW;
	window.lpfnWndProc = MessageHandler;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = hInstance;
	window.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hbrBackground = ((HBRUSH)GetStockObject(WHITE_BRUSH));
	window.lpszMenuName = NULL;
	window.lpszClassName = "RulerOverlay";

	assert(RegisterClass(&window));

	hWnd = CreateWindow("RulerOverlay", "WindowTitle", WS_OVERLAPPED,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
		0, 0, hInstance, 0);

	ShowWindow(hWnd, nCmdShow);
	SetForegroundWindow(hWnd);
	UpdateWindow(hWnd);

	while (true)
	{
		BOOL result = GetMessage(&msg, 0, 0, 0);
		if (result > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else
		{
			return result;
		}
	}


}