#include "Wiatr.h"

float Wiatr::wspolczynnikSilyWiatru[10] = { 0, 3, 2, 0, 0, 0, 0, 0, 0, 0 };
float Wiatr::silaWiatru[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const static int ILOSC_SIL_BRANE_POD_UWAGE = 3;

float * Wiatr::pobierzSileWiatru(float x, float z)
{

	float punkty[10][2] = { { 1, 1 },{ 13, 13 },{ 2, 2 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 } } ;
	float odleglosci[10];
	float sily[10][2];
	float sila[2] = {0,0};

	for (int i = 0; i < ILOSC_SIL_BRANE_POD_UWAGE; i++){
		odleglosci[i] = sqrt(((x - punkty[i][0])*(x - punkty[i][0])) + ((z - punkty[i][1])*(z - punkty[i][1])));
		if (odleglosci[i] < 1)
			odleglosci[i] = 1;
		sily[i][0] = silaWiatru[i] / (odleglosci[i]*10);
		sily[i][1] = silaWiatru[i] / (odleglosci[i]*10);
		sila[0] += sily[i][0];
		sila[1] += sily[i][1];
	}
	return sila;
}

void Wiatr::aktualizuj()
{
	for (int i = 0; i < ILOSC_SIL_BRANE_POD_UWAGE; i++)
	{
		wspolczynnikSilyWiatru[i] += 0.05;
		silaWiatru[i] = sin(wspolczynnikSilyWiatru[i]) ;
	}

}

Wiatr::Wiatr()
{

}


Wiatr::~Wiatr()
{
}
