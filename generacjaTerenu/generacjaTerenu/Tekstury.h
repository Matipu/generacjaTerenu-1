#pragma once
#include "GL/glew.h"
#include <vector>
#include "GL/GLAux.h"




class Tekstury
{
public:
	const static int TEXTURA_TRAWA = 0;
	const static int TEXTURA_TRAWA2 = 1;
	const static int TEXTURA_TRAWA3 = 2;
	const static int TEXTURA_TRAWA4 = 3;
	const static int TEXTURA_LISCIE = 4;
	const static int TEXTURA_KORA = 5;
	const static int TEXTURA_NIEBO = 6;
	static GLuint	texture[10];
	static GLuint trawa;
public:
	void static init();
	GLuint static addAplpha(char *Filename, int i, float red, float green, float blue, float delta);
	int static LoadGLTextures();
	Tekstury();
	~Tekstury();
	GLuint static tekstura(int ktora);
};

