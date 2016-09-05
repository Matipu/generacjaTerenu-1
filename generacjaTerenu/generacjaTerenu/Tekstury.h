#pragma once
#include "GL/glew.h"
#include <vector>
#include "GL/GLAux.h"




class Tekstury
{
public:
	static GLuint	texture[5];
	static GLuint trawa;
public:
	void static init();
	GLuint static addAplpha(char *Filename, int i, float red, float green, float blue, float delta);
	int static LoadGLTextures();
	Tekstury();
	~Tekstury();
	GLuint static tekstura(int ktora);
};

