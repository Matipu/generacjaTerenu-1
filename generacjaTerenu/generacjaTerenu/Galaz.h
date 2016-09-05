#pragma once
#include <vector>
#include"Tekstury.h"
using std::vector;
class Galaz
{
protected:
	Galaz* prev;
	vector<Galaz*> next;
	float pozycja[3];
	float grubosc;
	float obudowa[4][3];
public:
	Galaz(float pozycja[3], float grubosc, Galaz* prev, float obudowa[4][3]);
	~Galaz();
	virtual void Rysuj() = 0;
	virtual void rysujGalezie(bool czyLiscie) = 0;
	float* getPosition();
	vector<Galaz*>* getNext();
	float* getObudowaPoint(int index);
	void setObudowaPoint(int index, float point[3]);
	void Galaz::setObudowa(float matrix[4][3]);
};

