#pragma once
#include "GalazOpenGL.h"
#include <Windows.h>
#include "GL/glew.h"
#include "OperacjeNaWektorach.h"
#include <cstdlib>
#include <time.h>
#include<math.h>

class Drzewo
{
public:
	static const int ROZGALEZIONE = 0;
	static const int NIEROZGALEZIONE = 1;
	static const float skala;
protected:
	int maxIloscIteracji = 4;
	int iteracja;
	float szerokoscPnia;
	float pozycjaDrzewa[3];
	float szansaNaGalaz;
	int maxIloscRozgalezien;
	int typDrzewa;
	Galaz * pien;
	int iloscPni;
	
	void generujDrzewo(float maxDlugosc, Galaz* galaz, float szerokoscGalezi);
	static OperacjeNaWektorach operacjeNaWektorach;
	void stworzObudowe(float obudowa[4][3], float wysokosc, float szerokoscPnia);
	void obroc(float pozycjaGalezi[3], float obudowa[4][3], float obrot[3]);
	void znajdzKatyObrotuGalezi(float katyObrotu[5][3], float iloscRozgalezien);
	void losujObrot(float obrot[3]);
	void Drzewo::poGeneracjiKolejnejGalezi(float & maxDlugosc, float & szerokoscGalezi);
	void Drzewo::przedGeneracjaKolejnejGalezi(float & maxDlugosc, float & szerokoscGalezi);

public:
	Drzewo(float pozycjaDrzewa[3], int typDrzewa);
	~Drzewo();
	void Rysuj();
};

