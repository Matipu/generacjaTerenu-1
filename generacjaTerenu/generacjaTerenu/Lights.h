#pragma once
#include "GL/glew.h"
class Lights
{
protected:
	float natezenie_tla = 1.0;
	void mlecznaZarowka(float jasnosc);
public:
	Lights();
	~Lights();
	void obsluzOswietlenie();
    void changBackgroundLignt(float howMuch);
};

