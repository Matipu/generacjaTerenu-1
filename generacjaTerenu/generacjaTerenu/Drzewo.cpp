#include "Drzewo.h"

OperacjeNaWektorach Drzewo::operacjeNaWektorach;
 const float Drzewo::skala = 2.6f;
void dodaj(float obudowa[4][3], float pozycjaDrzewa[3])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			obudowa[i][j] += pozycjaDrzewa[j];
		}
	}
}
void Drzewo::obroc(float pozycjaGalezi[3], float obudowa[4][3], float obrot[3])
{
	if (obrot[2] != 0)
	{
		operacjeNaWektorach.obrocZ(pozycjaGalezi, 1.67f / 90.0f*obrot[2]);
		for (int i = 0; i < 4; i++) {
			operacjeNaWektorach.obrocZ(obudowa[i], 1.67f / 90.0f*obrot[2]);
		}
	}

	if (obrot[1] != 0)
	{
		operacjeNaWektorach.obrocY(pozycjaGalezi, 1.67f / 90.0f*obrot[1]);
		for (int i = 0; i < 4; i++) {
			operacjeNaWektorach.obrocY(obudowa[i], 1.67f / 90.0f*obrot[1]);
		}
	}

	if (obrot[0] != 0)
	{
		operacjeNaWektorach.obrocX(pozycjaGalezi, 1.67f / 90.0f*obrot[0]);
		for (int i = 0; i < 4; i++) {
			operacjeNaWektorach.obrocX(obudowa[i], 1.67f / 90.0f*obrot[0]);
		}
	}


}
void Drzewo::stworzObudowe(float obudowa[4][3], float wysokosc, float szerokoscPnia)
{
	float obudowaTmp[4][3] = {
		{ -szerokoscPnia, wysokosc , szerokoscPnia },
		{ szerokoscPnia, wysokosc , szerokoscPnia },
		{ -szerokoscPnia, wysokosc , -szerokoscPnia },
		{ szerokoscPnia, wysokosc , -szerokoscPnia }
	};

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			obudowa[i][j] = obudowaTmp[i][j];
}
void Drzewo::losujObrot(float obrot[3])
{
	if (typDrzewa == Drzewo::NIEROZGALEZIONE) {
		obrot[0] = 0;
		obrot[1] = (float)(rand() % 10);
		obrot[2] = (float)(rand() % 4);
	}
	if (typDrzewa == Drzewo::ROZGALEZIONE) {
		obrot[0] = 0;
		obrot[1] = (float)(rand() % 360);
		obrot[2] = (float)(rand() % 50 + 30);
	}
}
void Drzewo::znajdzKatyObrotuGalezi(float katyObrotu[5][3], float iloscRozgalezien)
{
	bool przelosuj = true;
	do
	{
		przelosuj = false;
		for (int i = 0; i < (int)iloscRozgalezien; i++) {
			losujObrot(katyObrotu[i]);
		}
		for (int i = 0; i < (int)iloscRozgalezien; i++) {
			for (int j = 0; j < (int)iloscRozgalezien; j++) {
				if (j != i){
					float kat1 = katyObrotu[i][1];
					float kat2 = katyObrotu[j][1];
					if (abs(kat1 - kat2) < 50){
						przelosuj = true;
					}
				}
			}
		}

	} while (przelosuj!=false);


}
void Drzewo::poGeneracjiKolejnejGalezi(float & maxDlugosc, float & szerokoscGalezi)
{
	if (typDrzewa == Drzewo::NIEROZGALEZIONE) {
		maxDlugosc /= 1.4;
		szerokoscGalezi *= 1.1;
	}
	if (typDrzewa == Drzewo::ROZGALEZIONE) {
		maxDlugosc *= 2;
		szerokoscGalezi = szerokoscGalezi * 4 / 3;
	}
}
void Drzewo::przedGeneracjaKolejnejGalezi(float & maxDlugosc, float & szerokoscGalezi)
{
	if (typDrzewa == Drzewo::NIEROZGALEZIONE) {
		
		maxDlugosc = maxDlugosc * 1.4;
		szerokoscGalezi /= 1.1;
	}
	if (typDrzewa == Drzewo::ROZGALEZIONE) {
		maxDlugosc /= 1.8;
		szerokoscGalezi = szerokoscGalezi/4*3;
	}
}

void Drzewo::generujDrzewo(float maxDlugosc, Galaz* galaz, float szerokoscGalezi)
{
	iteracja++;
	if (iteracja > maxIloscIteracji){
		iteracja--;
		return;
	}
	if (iteracja == maxIloscIteracji && maxIloscIteracji != 1) {
		szerokoscGalezi = 0.0f;
	}

	vector<Galaz*>* next = galaz->getNext();

	float katyObrotu[5][3];
	float iloscRozgalezien = (maxIloscRozgalezien);
	znajdzKatyObrotuGalezi(katyObrotu, iloscRozgalezien);

	for (int i = 0; i < iloscRozgalezien; i++){

		int dlugoscLosowa = (int)(maxDlugosc * 1000 )/2;
		int dlugoscPodstawowa = (int)(maxDlugosc * 1000)/2;
		float dlugosc = (float)((rand() % dlugoscLosowa) + dlugoscPodstawowa) / 1000.0;
		float pozycjaGalezi[3] = {0, dlugosc, 0 };
		float obudowa[4][3];

		stworzObudowe(obudowa, dlugosc, szerokoscGalezi);
		obroc(pozycjaGalezi, obudowa, katyObrotu[i]);
		
		for (int j = 0; j < 3; j++) {
			pozycjaGalezi[j] += galaz->getPosition()[j];
		}
		dodaj(obudowa, galaz->getPosition());

		next->push_back(new GalazOpenGL(pozycjaGalezi, szerokoscGalezi, galaz, obudowa, katyObrotu[i]));

		przedGeneracjaKolejnejGalezi(maxDlugosc, szerokoscGalezi);
		generujDrzewo(maxDlugosc, (*next)[i] , szerokoscGalezi);
		poGeneracjiKolejnejGalezi(maxDlugosc, szerokoscGalezi);

	}
	iteracja--;
}

Drzewo::Drzewo(float pozycjaDrzewa[3], int typDrzew)
{
	this->typDrzewa = typDrzewa;
	if (typDrzewa == Drzewo::NIEROZGALEZIONE){
		szansaNaGalaz = 0.1;
		maxIloscRozgalezien = 1;
		maxIloscIteracji = 3;
	}
	if (typDrzewa == Drzewo::ROZGALEZIONE){
		szansaNaGalaz = 0.1;
		maxIloscRozgalezien = 3;
		maxIloscIteracji = 3;
	}
	iteracja = 0;

	float szerokoscGalezi = 0.04f*skala;
	szerokoscPnia = szerokoscGalezi;
	float obudowa[4][3];
	stworzObudowe(obudowa, 0, szerokoscGalezi);

	szerokoscGalezi /= 2;
	dodaj(obudowa, pozycjaDrzewa);
	float obrot[3] = { 0, 0, 0 };
	pien = new GalazOpenGL(pozycjaDrzewa, szerokoscGalezi, nullptr, obudowa, obrot);


	if (typDrzewa == Drzewo::ROZGALEZIONE) {
		int tmp1 = this->maxIloscRozgalezien;
		int tmp2 = this->maxIloscIteracji;
		this->maxIloscRozgalezien = 1;
		this->maxIloscIteracji = 1;
		this->typDrzewa = Drzewo::NIEROZGALEZIONE;
		iloscPni = 3;
		//for (int i = 0; i < 3; i++)
		//{
			generujDrzewo(0.12f*skala, pien, szerokoscGalezi);
			generujDrzewo(0.12f*skala, (*(pien->getNext()))[0], szerokoscGalezi*0.95);
			generujDrzewo(0.12f*skala, (*(*(pien->getNext()))[0]->getNext())[0], szerokoscGalezi*0.90);
		//}

		this->typDrzewa = Drzewo::ROZGALEZIONE;
		this->maxIloscRozgalezien = tmp1;
		this->maxIloscIteracji = tmp2;
		
		generujDrzewo(0.2f*skala, (*(*(*(pien->getNext()))[0]->getNext())[0]->getNext())[0], szerokoscGalezi / 2);


	}
	else{
		generujDrzewo(0.4f*skala, pien, szerokoscGalezi);
	}


	
}

Drzewo::~Drzewo()
{
}

void Drzewo::Rysuj()
{
	pien->Rysuj();
	pien->rysujGalezie(false);

}
