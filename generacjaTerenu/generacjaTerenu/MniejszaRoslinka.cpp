#include "MniejszaRoslinka.h"

Wiatr MniejszaRoslinka::wiatr;

MniejszaRoslinka::MniejszaRoslinka(float x, float y, float z, long tekstura, float scale):tekstura(tekstura)
{
	pozycja = new float[3];
	pozycja[0] = x;
	pozycja[1] = y; 
	pozycja[2] = z;
	this->scale = scale;
}

MniejszaRoslinka::MniejszaRoslinka(float * pozycja, GLuint tekstura, float scale)
{
	this->tekstura = tekstura;
	this->pozycja = new float[3];
	this->pozycja[0] = pozycja[0];
	this->pozycja[1] = pozycja[1]+scale;
	this->pozycja[2] = pozycja[2];
	this->scale = scale;
}

MniejszaRoslinka::~MniejszaRoslinka()
{
	delete[] pozycja;

}

static bool pomniejszanie = true;
void MniejszaRoslinka::rysuj()
{
	//glFrontFace(GL_CW);    // albo CW, zale¿y jak le¿y ;p
	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tekstura);

	glBegin(GL_QUADS);
	float x = pozycja[0];
	float y = pozycja[1];
	float z = pozycja[2];
	float* sila = wiatr.pobierzSileWiatru(x, z);
	float vector1[3] = { x - scale, y - scale, z - scale };
	float vector2[3] = { x - scale + sila[0], y + scale, z - scale + sila[1] };
	float vector3[3] = { x + scale, y - scale, z + scale };
	float vector4[3] = { x + scale + sila[0], y + scale, z + scale + sila[1] };

	
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

	
	float vector5[3] = { x - scale, y - scale, z + scale };
	float vector6[3] = { x - scale + sila[0], y + scale, z + scale + sila[1] };
	float vector7[3] = { x + scale + sila[0], y + scale, z - scale + sila[1] };
	float vector8[3] =  { x + scale, y - scale, z - scale };
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
