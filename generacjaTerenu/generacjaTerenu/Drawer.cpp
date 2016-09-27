#include "Drawer.h"

Drawer::Drawer(HDC * dcHandle)
{
	this->dcHandle = dcHandle;
}


Drawer::~Drawer()
{
}

void Drawer::drawTriangle()
{
	glBegin(GL_TRIANGLES);

	glVertex3f(-2, -1, 0);
	glVertex3f(2, -1, 0);
	glVertex3f(1, 1, 0);

	glEnd();

}
void Drawer::drawRectangle(float x, float y, float z)
{
	glBegin(GL_QUADS);

	float x2 = x / 2;
	float y2 = y / 2;
	float z2 = z / 2;
	glVertex3f(x2, -y2, -z2);
	glVertex3f(-x2, -y2, -z2);
	glVertex3f(-x2, -y2, z2);
	glVertex3f(x2, -y2, z2);


	glEnd();
}
void Drawer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0, 0, -10.0);
	drawRectangle(1, 1, 1);
	SwapBuffers(*dcHandle);
}
