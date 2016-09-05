#pragma once
#include "Okno.h"
#include <Windows.h>
#include "GL/glew.h"
#include "Drawer.h"

class OknoOpenGL :
	public Okno
{
protected:
	Drawer drawer;
	HGLRC rcHandle;
	HDC dcHandle;
	bool initWGL(HWND handle);
	bool deinitWGL(HWND handle);
	bool setPixelFormat(HDC handle);
	void createScene();
public:
	OknoOpenGL();
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
};
static OknoOpenGL window;

