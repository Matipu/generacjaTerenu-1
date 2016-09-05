#include "GalazOpenGL.h"

OperacjeNaWektorach GalazOpenGL::operacjeNaWektorach;

GalazOpenGL::GalazOpenGL(float pozycja[3], float grubosc, Galaz* prev, float obudowa[4][3], float obrot[3])
	:Galaz(pozycja, grubosc, prev, obudowa)
{
	for (int i = 0; i < 3; i++)
	{
		this->obrot[i] = obrot[i];
	}
}


GalazOpenGL::~GalazOpenGL()
{
}

void GalazOpenGL::Rysuj()
{
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT_AND_BACK);
	glBegin(GL_QUADS);
	
	if (prev)
	{
		//for (int i = 0; i < 4; i++)
		//{
		//	glVertex3fv(prev->getObudowaPoint(i));
		//	glVertex3fv(obudowa[i]);
		//}

		float wynik[3];
		glNormal3fv(operacjeNaWektorach.jednostkowyWektorNormalny3fv(obudowa[2], obudowa[0], prev->getObudowaPoint(0), wynik));
		glVertex3fv(obudowa[2]);
		glVertex3fv(obudowa[0]);
		glVertex3fv(prev->getObudowaPoint(0));
		glVertex3fv(prev->getObudowaPoint(2));
		
		
		float wynik2[3];
		glNormal3fv(operacjeNaWektorach.jednostkowyWektorNormalny3fv(obudowa[0], obudowa[1], prev->getObudowaPoint(1), wynik2));
		glVertex3fv(obudowa[0]);
		glVertex3fv(obudowa[1]);
		glVertex3fv(prev->getObudowaPoint(1));
		glVertex3fv(prev->getObudowaPoint(0));
		
		float wynik3[3];
		glNormal3fv(operacjeNaWektorach.jednostkowyWektorNormalny3fv(obudowa[1], obudowa[3], prev->getObudowaPoint(3), wynik3));
		glVertex3fv(obudowa[1]);
		glVertex3fv(obudowa[3]);
		glVertex3fv(prev->getObudowaPoint(3));
		glVertex3fv(prev->getObudowaPoint(1));
		
		float wynik4[3];
		glNormal3fv(operacjeNaWektorach.jednostkowyWektorNormalny3fv(obudowa[3], obudowa[2], prev->getObudowaPoint(2), wynik4));
		glVertex3fv(obudowa[3]);
		glVertex3fv(obudowa[2]);
		glVertex3fv(prev->getObudowaPoint(2));
		glVertex3fv(prev->getObudowaPoint(3));
	}
	for (int i = 0; i < next.size(); i++)
	{
		next[i]->Rysuj();
	}

	glEnd();
}