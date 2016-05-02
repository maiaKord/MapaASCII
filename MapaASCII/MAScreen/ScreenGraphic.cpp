#pragma once
#include "ScreenGraphic.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

ScreenGraphic::ScreenGraphic()
{
}

int ScreenGraphic::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	zhInstance = hInstance;

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = zhInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = appName;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(0, L"Error Registering Class!", L"Error!", MB_ICONSTOP | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_STATICEDGE, WndClass.lpszClassName, L"MapaASCII", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, getBackBufferWidth(), getBackBufferHeight(), NULL, NULL, zhInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(0, L"Error Creating Window!", L"Error!", MB_ICONSTOP | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	return Msg.wParam;
}

void ScreenGraphic::update()
{
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void ScreenGraphic::print()
{
}

void ScreenGraphic::printText(int x, int y, const char* text)
{

}

void ScreenGraphic::clear()
{

}

