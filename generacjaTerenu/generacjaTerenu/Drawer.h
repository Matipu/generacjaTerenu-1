#pragma once
#include <Windows.h>
#include "GL/glew.h"

class Drawer
{
protected:
	HDC * dcHandle;
	void drawTriangle();
	void drawRectangle(float x, float y, float z);
public:
	Drawer(HDC * dcHandle);
	~Drawer();
	void draw();
};

