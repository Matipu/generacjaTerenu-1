#pragma once

#include <Windows.h>
#include "GL/glew.h"
#include <GL/freeglut.h>
#include "Galaz.h"
#include "OperacjeNaWektorach.h"
#include "Wiatr.h"
class GalazOpenGL : public Galaz
{
	float obrot[3];
	static OperacjeNaWektorach operacjeNaWektorach;
	Tekstury tekstury;
public:
	static Wiatr wiatr;
	GalazOpenGL(float pozycja[3], float grubosc, Galaz* prev, float obudowa[4][3], float obrot[3]);
	~GalazOpenGL();
	void Rysuj();
	void rysujGalezie(bool czyLiscie);
};

