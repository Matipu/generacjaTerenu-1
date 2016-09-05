#include "GalazOpenGL.h"

OperacjeNaWektorach GalazOpenGL::operacjeNaWektorach;
Wiatr GalazOpenGL::wiatr;

GalazOpenGL::GalazOpenGL(float pozycja[3], float grubosc, Galaz* prev, float obudowa[4][3], float obrot[3])
	:Galaz(pozycja, grubosc, prev, obudowa){

	for (int i = 0; i < 3; i++){
		this->obrot[i] = obrot[i];
	}
	tekstury.init();
}


GalazOpenGL::~GalazOpenGL(){

}

void GalazOpenGL::rysujGalezie(bool czyLiscie)
{
	glColor3f(0.2, 0.6f, 0.2);
	if (czyLiscie ){
		for (int i = 0; i < next.size(); i++){
			//glTranslatef((pozycja[0] + next[i]->getPosition()[0])/2, (pozycja[1] + next[i]->getPosition()[1]) / 2, (pozycja[2] + next[i]->getPosition()[2]) / 2);
			//glScalef(1, 0.6, 1);
			//glutSolidSphere((1 / (grubosc * 1500)), 10, 10);
			//glScalef(1, 1 / 0.6, 1);
			//glTranslatef((pozycja[0] + next[i]->getPosition()[0]) / -2, (pozycja[1] + next[i]->getPosition()[1]) / -2, (pozycja[2] + next[i]->getPosition()[2]) / -2);

			float scale = 0.1f;
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, tekstury.tekstura(4));
			
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
			float vector8[3] = { x + scale, y - scale, z - scale };
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

	}
	
	for (int i = 0; i < next.size(); i++){
		next[i]->rysujGalezie(true);
	}

}
void GalazOpenGL::Rysuj()
{
	glColor3f(0.5, 0.25, 0);
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT_AND_BACK);
	glBegin(GL_QUADS);
	
	if (prev){

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