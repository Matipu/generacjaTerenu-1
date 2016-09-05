#pragma once
#include "GL/glew.h"
#include <math.h>
#include "Wiatr.h"
class MniejszaRoslinka
{
	float* pozycja;
	GLuint tekstura;
	float scale;
public:
	static Wiatr wiatr;
	MniejszaRoslinka(float x, float y, float z, long tekstura, float scale);
	MniejszaRoslinka(float * pozycja, GLuint tekstura, float scale);
	~MniejszaRoslinka();
	void rysuj();
};

