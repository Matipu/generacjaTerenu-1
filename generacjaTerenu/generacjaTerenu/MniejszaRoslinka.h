#pragma once
#include "GL/glew.h"
#include "Definicje.h"
#include <math.h>
#include "Wiatr.h"
#include <stdlib.h>
class MniejszaRoslinka
{
	float* pozycja;
	GLuint tekstura;
	float scaleX;
	float scaleY;
	float scaleZ;
	float* maxWychylenie;
	float* wychylenie;
	float* sztywnosc;
public:
	static Wiatr wiatr;
	MniejszaRoslinka(float x, float y, float z, long tekstura, float scale);
	MniejszaRoslinka(float * pozycja, GLuint tekstura, float scale);
	~MniejszaRoslinka();
	void rysuj();
};

