#pragma once
#include<math.h>
class Wiatr
{
	static float wspolczynnikSilyWiatru[10];
	static float silaWiatru[10][2];
public:
	static float* pobierzSileWiatru(float x, float z);
	static void aktualizuj();
	Wiatr();
	~Wiatr();
};

