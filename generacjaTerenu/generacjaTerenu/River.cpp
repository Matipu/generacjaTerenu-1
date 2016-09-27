#include "River.h"



River::River(int _WysokoscMIN, int  _WysokoscMAX, int _MIN_X, int _MIN_Z, int _MAX_X, int _MAX_Z)
{
	WysokoscMIN = _WysokoscMIN;
	WysokoscMAX = _WysokoscMAX;
	MIN_X = _MIN_X;
	MIN_Z = _MIN_Z;
	MAX_X = _MAX_X;
	MAX_Z = _MAX_Z;
}


void River::CreateRiver(float terrain[terrain_size][terrain_size])
{
	float RiverBed[terrain_size][terrain_size];
	RiverPath riverPath = RiverPath();
	riverPath.FindPath(MAX_X, MAX_Z, MIN_X, MIN_Z, terrain, WysokoscMAX, WysokoscMIN);
	std::vector<RiverPoint*>Path = riverPath.GetPath(WysokoscMIN);
	float HeightABS, DeltaHeight;
	float Denivelation = WysokoscMAX - WysokoscMIN;
	//Tworzenie Riverbed  - tablica z wagami do obliczeñ przy dr¹¿eniu koryta rzeki
	for (int i = 0; i<terrain_size; i++)
		for (int j = 0; j < terrain_size; j++)
		{
			RiverBed[i][j] = 0;
			RiverMask[i][j] = 0;
			RiverModel[i][j] = 0;
		}
	for (int x = 0; x < Path.size(); x++) {
		int PathX = Path[x]->Get_X();
		int PathZ = Path[x]->Get_Z();
		float RiverHeight = (terrain[PathX][PathZ] - WysokoscMIN) - (Denivelation*0.18) + WysokoscMIN;
		for (int m = PathX - 4; m <= PathX + 4; m++) {
			for (int n = PathZ - 4; n <= PathZ + 4; n++)
			{
				if (m < 0 || n < 0 || m >= terrain_size || n >= terrain_size) continue;
				float radius = (float)sqrt(((m - PathX)*(m - PathX)) + ((n - PathZ)*(n - PathZ)));
				if (radius < 0.5f && RiverBed[m][n] < 0.3f)
				{
					RiverBed[m][n] = 0.3f;
					RiverMask[m][n] = true;
				}
				else if (radius >= 1.0f && radius < 2.3f && RiverBed[m][n] < 0.25f)
				{
					RiverBed[m][n] = 0.25f;
					RiverMask[m][n] = true;
				}
				else if (radius > 2.7f && radius < 3.0f && RiverBed[m][n] < 0.2f)
				{
					RiverBed[m][n] = 0.2f;
					RiverMask[m][n] = true;
				}
				else if (radius >= 3 && radius <= 4.3 && RiverBed[m][n] < 0.15f)
				{
					RiverBed[m][n] = 0.15f;
					RiverMask[m][n] = true;
				}
				else if (radius > 4.3 && radius < 5 && RiverBed[m][n] == 0)
				{
					RiverMask[m][n] = true;
				}

				RiverModel[m][n] = RiverHeight;
			}
		}

	}
	//Dr¹¿enie rowu dla rzeki
	//Denivelation = WysokoscMAX - WysokoscMIN;
	for (int i = 0; i<terrain_size; i++)
		for (int j = 0; j < terrain_size; j++)
		{
			HeightABS = (terrain[i][j] - WysokoscMIN);
			DeltaHeight = Denivelation*RiverBed[i][j];
			terrain[i][j] = (HeightABS - DeltaHeight) + WysokoscMIN;
		}
}


void River::RenderRiver(float terrain[terrain_size][terrain_size])
{
	glShadeModel(GL_SMOOTH);
	glColor3f(0.1f, 0.6f, 0.1f);

	for (int x = 0; x < terrain_size - 1; ++x) {
		for (int z = 0; z < terrain_size - 1; ++z) {
			if (RiverMask[x][z] == 0.0) continue;
			glColor3f(0.4f, 0.6f, 0.4f);
			const float scale = terrain_scale;

			///
			bool korytoRzeki = false;
			int iloscPol = 0;
			for (int m = x; m <= x + 1; m++)
				for (int n = z; n <= z + 1; n++)
				{
					if (n == -1 && m == -1 && n == terrain_size && m == terrain_size) continue;
					if (RiverMask[m][n])
						iloscPol++;
				}
			if (iloscPol <= 3) continue;
			glEnable(GL_TEXTURE_2D);
			bool los = rand() % 2;
			if (los)
				glBindTexture(GL_TEXTURE_2D, Tekstury::tekstura(8));
			else
				glBindTexture(GL_TEXTURE_2D, Tekstury::tekstura(9));
			glBegin(GL_QUADS);
			float vector1[3] = { x*scale, RiverModel[x][z] * scale, z*scale };
			float vector2[3] = { x*scale, RiverModel[x][z + 1] * scale, (z + 1)*scale };
			float vector3[3] = { (x + 1)*scale, RiverModel[x + 1][z + 1] * scale, (z + 1)*scale };
			float vector4[3] = { (x + 1)*scale, RiverModel[x + 1][z] * scale, z*scale };
			float wynik[3];
			glNormal3fv(OperacjeNaWektorach().jednostkowyWektorNormalny3fv(vector1, vector2, vector3, wynik));
			glNormal3f(0, 1, 0);
			glVertex3fv(vector1);
			glTexCoord2f(1.0f, 0.0f);

			glNormal3f(0, 1, 0);
			glVertex3fv(vector2);
			glTexCoord2f(1.0f, 1.0f);

			glNormal3f(0, 1, 0);
			glVertex3fv(vector3);
			glTexCoord2f(0.0f, 1.0f);

			glNormal3f(0, 1, 0);
			glVertex3fv(vector4);
			glTexCoord2f(0.0f, 0.0f);



			glDisable(GL_TEXTURE_2D);
			glEnd();
		}
	}
}

River::~River()
{
}
