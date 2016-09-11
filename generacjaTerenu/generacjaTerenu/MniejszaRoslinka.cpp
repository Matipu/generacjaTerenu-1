#include "MniejszaRoslinka.h"

Wiatr MniejszaRoslinka::wiatr;

MniejszaRoslinka::MniejszaRoslinka(float x, float y, float z, long tekstura, float scale):tekstura(tekstura)
{
	pozycja = new float[3];
	pozycja[0] = x;
	pozycja[1] = y; 
	pozycja[2] = z;
	
	this->scaleX = scale * 0.6;
	this->scaleY = scale* 0.6;
	this->scaleZ = scale * 0.6;

	this->maxWychylenie = new float[2];
	maxWychylenie[0] = 0.1;
	maxWychylenie[1] = 0.1;

	this->wychylenie = new float[2];
	wychylenie[0] = 0;
	wychylenie[1] = 0;
}

MniejszaRoslinka::MniejszaRoslinka(float * pozycja, GLuint tekstura, float scale)
{
	this->tekstura = tekstura;
	this->pozycja = new float[3];
	this->pozycja[0] = pozycja[0];
	this->pozycja[1] = pozycja[1]+scale;
	this->pozycja[2] = pozycja[2];
	this->scaleX = scale * 0.6;
	this->scaleY = scale * 0.6;
	this->scaleZ = scale * 0.6;

	this->maxWychylenie = new float[2];
	maxWychylenie[0] = 0.1;
	maxWychylenie[1] = 0.1;

	this->wychylenie = new float[2];
	wychylenie[0] = 0;
	wychylenie[1] = 0;

	this->sztywnosc = new float[2];
	sztywnosc[0] = ((rand() % 20) + 70.0f)/100.0f;
	sztywnosc[1] = ((rand() % 20) + 70.0f) / 100.0f;
}

MniejszaRoslinka::~MniejszaRoslinka()
{
	delete[] pozycja;
}

static bool pomniejszanie = true;
void MniejszaRoslinka::rysuj()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tekstura);

	glBegin(GL_QUADS);
	float x = pozycja[0];
	float y = pozycja[1];
	float z = pozycja[2];


	float* sila = wiatr.pobierzSileWiatru(x, z);
	wychylenie[0] += sila[0]*2;
	wychylenie[1] += sila[1]*2;

	
	wychylenie[0] -= (maxWychylenie[0] - (maxWychylenie[0] - wychylenie[0]))*sztywnosc[0];
	wychylenie[1] -= (maxWychylenie[1] - (maxWychylenie[1] - wychylenie[1]))*sztywnosc[1];


	float vector1[3] = { x - scaleX, y - scaleY, z - scaleZ };
	float vector2[3] = { x - scaleX + wychylenie[0], y + scaleY, z - scaleZ + wychylenie[1] };
	float vector3[3] = { x + scaleX, y - scaleY, z + scaleZ };
	float vector4[3] = { x + scaleX + wychylenie[0], y + scaleY, z + scaleZ + wychylenie[1] };

	
	glNormal3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vector1);

	glNormal3f(0, 1, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vector2);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vector4);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vector3);

	
	float vector5[3] = { x - scaleX, y - scaleY, z + scaleZ };
	float vector6[3] = { x - scaleX + wychylenie[0], y + scaleY, z + scaleZ + wychylenie[1] };
	float vector7[3] = { x + scaleX + wychylenie[0], y + scaleY, z - scaleZ + wychylenie[1] };
	float vector8[3] =  { x + scaleX, y - scaleY, z - scaleZ };
	glNormal3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vector5);

	glNormal3f(0, 1, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vector6);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vector7);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vector8);
	

	glEnd();
	glDisable(GL_TEXTURE_2D);
}
