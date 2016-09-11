#include "OknoOpenGL.h"
#include "GLUTWindow.h"
/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return window.WndProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!window.rejestrujOkno(hInstance, { 25,25 }, { 1400, 700 }, (WNDPROC)::WndProc))
	{

		return EXIT_FAILURE;
	}

	return window.run();
}*/

 

int main(int argc, char** argv) {

	Tekstury tekstury;
	GLUTWindow window(&argc, argv);
	window.init();
	return 0;
}


