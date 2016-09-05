#include "Tekstury.h"

GLuint Tekstury::trawa = -1;
GLuint Tekstury::texture[5];
/**/
AUX_RGBImageRec *LoadBMP(char *Filename) {				// Loads A Bitmap Image
	FILE *File = NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File = fopen(Filename, "r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

GLuint Tekstury::addAplpha(char *Filename, int i, float red, float green, float blue, float delta)
{
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage, 0, sizeof(void *) * 1);           	// Set The Pointer To NULL

	BYTE * dane1;											// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0] = LoadBMP(Filename))
	{								// Set The Status To TRUE

		int w = ((TextureImage[0]->sizeX) * 4) * TextureImage[0]->sizeY;
		dane1 = new BYTE[w];

		int k = 0, l = 0;
		while (k < w)
		{
			dane1[k] = TextureImage[0]->data[l];
			dane1[k + 1] = TextureImage[0]->data[l + 1];
			dane1[k + 2] = TextureImage[0]->data[l + 2];
			if (pow(red - TextureImage[0]->data[l + 2],2)  < delta*delta && 
				pow(green - TextureImage[0]->data[l], 2) < delta*delta &&
					pow(blue - TextureImage[0]->data[l + 1], 2) < delta*delta) {
				dane1[k + 3] = 0; 
			}
			else dane1[k + 3] = 255;
				

			k += 4;
			l += 3;
		}

		glGenTextures(1, &texture[i]);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexImage2D(GL_TEXTURE_2D, //rodzaj tworzonej tekstury (1, 2 czy 3-wymiarowa)
			0, //poziom mipmapy
			GL_RGBA, //wewn?trzny format danych tekstury
			TextureImage[0]->sizeX, //szeroko?? obrazu tekstury
			TextureImage[0]->sizeY, //wysoko?? obrazu tekstury
			0, //ilo?? pikseli ramki
			GL_RGBA, //format koloru
			GL_UNSIGNED_BYTE, //format danych reprezentuj?cych piksel
			dane1); //bufor danych tekstury

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}



	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	return 1;
}

int Tekstury::LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status = FALSE;									// Status Indicator
	addAplpha("Data/trawa2.bmp", 0, 0 ,0 ,0 ,10);
	addAplpha("Data/trawa.bmp", 1, 0, 0, 0, 10);
	addAplpha("Data/trawa3.bmp", 2, 0, 0, 0, 10);
	addAplpha("Data/grass.bmp", 3, 0, 0, 0, 10);
	addAplpha("Data/liscie.bmp", 4, 255, 255, 255, 50);
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.666f);

	return Status;										// Return The Status
}

Tekstury::Tekstury(){

}

Tekstury::~Tekstury()
{
}

GLuint Tekstury::tekstura(int ktora){

	return  texture[ktora];
}

void Tekstury::init()
{

	if (trawa == -1) {
		LoadGLTextures();
			trawa = 5;
	}
}
