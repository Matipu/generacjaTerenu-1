#include "Galaz.h"

Galaz::Galaz(float pozycja[3], float grubosc, Galaz* prev, float obudowa[4][3])
	: grubosc(grubosc), prev(prev)
{
	for (int i = 0; i < 3; i++)
		this->pozycja[i] = pozycja[i];
	
	setObudowa(obudowa);
}


Galaz::~Galaz(){

}

float * Galaz::getPosition(){
	return pozycja;
}

vector<Galaz*>* Galaz::getNext(){
	return &next;
}

float * Galaz::getObudowaPoint(int index){
	return obudowa[index];
}

void Galaz::setObudowaPoint(int index, float point[3]){
	for (int i = 0; i < 3; i++) {
		obudowa[index][i] = point[i];
	}
}
void Galaz::setObudowa(float matrix[4][3]){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			obudowa[i][j] = matrix[i][j];
		}
	}
}
