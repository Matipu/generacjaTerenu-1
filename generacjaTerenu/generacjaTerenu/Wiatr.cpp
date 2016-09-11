#include "Wiatr.h"

float Wiatr::wspolczynnikSilyWiatru[10] = { 0, 3, 2, 0, 0, 0, 0, 0, 0, 0 };
float Wiatr::silaWiatru[10][2] = { {0,0},{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
const static int ILOSC_SIL_BRANE_POD_UWAGE = 3;

float * Wiatr::pobierzSileWiatru(float x, float z)
{

	float punkty[10][2] = { { 1, 1 },{ 13, 13 },{ 2, 2 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 },{ 5, 5 } } ;
	float odleglosci[10];
	float sily[10][2];
	float sila[2] = {0.0,0.1};
	
	for (int i = 0; i < ILOSC_SIL_BRANE_POD_UWAGE; i++){
		odleglosci[i] = sqrt(((x - punkty[i][0])*(x - punkty[i][0])) + ((z - punkty[i][1])*(z - punkty[i][1])));
		if (odleglosci[i] < 1)
			odleglosci[i] = 1;
		sily[i][0] = silaWiatru[i][0] / (odleglosci[i]*10);
		sily[i][1] = silaWiatru[i][1] / (odleglosci[i]*10);
		sila[0] += sily[i][0];
		sila[1] += sily[i][1];
	}
	return sila;
}

void Wiatr::aktualizuj()
{
	for (int i = 0; i < ILOSC_SIL_BRANE_POD_UWAGE; i++){
		wspolczynnikSilyWiatru[i] += 0.05;
		silaWiatru[i][0] = 0.8*sin(wspolczynnikSilyWiatru[i]) + 1.3*cos(wspolczynnikSilyWiatru[i]) + 0.2;
		silaWiatru[i][1] = 1.3*sin(wspolczynnikSilyWiatru[i]) + 0.8*cos(wspolczynnikSilyWiatru[i]) + 0.2;
	}

}

Wiatr::Wiatr()
{

}


Wiatr::~Wiatr()
{
}
