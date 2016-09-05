#pragma once
#include <math.h>
class OperacjeNaWektorach
{
public:
	float* roznica3fv(float punkt1[3], float punkt2[3], float wynik[3])
	{
		for (int i = 0; i <3; i++) {
			wynik[i] = punkt2[i] - punkt1[i];
		}
		return wynik;
	}
	float* iloczynWektorowy3fv(float a[3], float b[3], float wynik[3])
	{
		wynik[0] = a[1] * b[2] - a[2] * b[1];
		wynik[1] = -(a[0] * b[2] - a[2] * b[0]);
		wynik[2] = a[0] * b[1] - a[1] * b[0];
		return wynik;
	}
	float dlugoscWektora3fv(float wektor[3])
	{
		#define SQR(x) ((x)*(x))
		float dlugosc = 0;
		for (int i = 0; i <3; i++) {
			dlugosc += SQR(wektor[i]);
		}
		return sqrt(dlugosc);

	}
	float* normujWektor3fv(float wektor[3])
	{
		float dlugosc = dlugoscWektora3fv(wektor);
		for (int i = 0; i <3; i++) {
			wektor[i]/=dlugosc;
		}
		return wektor;
	}
public:
	OperacjeNaWektorach();
	float* jednostkowyWektorNormalny3fv(float punkt1[3], float punkt2[3], float punkt3[3], float wynik[3])
	{
		float data1[3];
		float data2[3];
		return wynik = normujWektor3fv(
			iloczynWektorowy3fv(roznica3fv(punkt1, punkt2, data1), roznica3fv(punkt1, punkt3, data2),wynik)
			);
	}
	~OperacjeNaWektorach();
	float* obrocZ(float p[3], float angle)
	{
		float s = sin(angle);
		float c = cos(angle);
		float m[3][3] = { { c,-s,0 },{ s,c,0 },{ 0,0,1 } };

		float wynik[3] = {
			m[0][0] * p[0] + m[0][1] * p[1] + m[0][2] * p[2],
			m[1][0] * p[0] + m[1][1] * p[1] + m[1][2] * p[2],
			m[2][0] * p[0] + m[2][1] * p[1] + m[2][2] * p[2]
		};
		p[0] = wynik[0];
		p[1] = wynik[1];
		p[2] = wynik[2];
		return p;
	}
	float* obrocY(float p[3], float angle)
	{
		float s = sin(angle);
		float c = cos(angle);
		float m[3][3] = { { c,0,s },{ 0,1,0 },{ -s,0,c } };

		float wynik[3] = {
			m[0][0] * p[0] + m[0][1] * p[1] + m[0][2] * p[2],
			m[1][0] * p[0] + m[1][1] * p[1] + m[1][2] * p[2],
			m[2][0] * p[0] + m[2][1] * p[1] + m[2][2] * p[2]
		};
		p[0] = wynik[0];
		p[1] = wynik[1];
		p[2] = wynik[2];
		return p;
	}
	float* obrocX(float p[3], float angle)
	{
		float s = sin(angle);
		float c = cos(angle);
		float m[3][3] = { { 1,0,0 },{ 0,c,-s },{ 0,s,c } };

		float wynik[3] = {
			m[0][0] * p[0] + m[0][1] * p[1] + m[0][2] * p[2],
			m[1][0] * p[0] + m[1][1] * p[1] + m[1][2] * p[2],
			m[2][0] * p[0] + m[2][1] * p[1] + m[2][2] * p[2]
		};
		p[0] = wynik[0];
		p[1] = wynik[1];
		p[2] = wynik[2];
		return p;
	}
};

