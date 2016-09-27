#pragma once
#include "Definicje.h"
#include "GL/glew.h"
#include "OperacjeNaWektorach.h"
#include "Tekstury.h"
#include "RiverPath.h"
#include "RiverPoint.h"
#include <cmath>
class River
{
	float WysokoscMIN;
	float WysokoscMAX;
	int MIN_X;
	int MIN_Z;
	int MAX_X;
	int MAX_Z;
public:
	River(int _WysokoscMIN,int _WysokoscMAX, int _MIN_X, int _MIN_Z, int _MAX_X, int _MAX_Z);
	bool RiverMask[terrain_size][terrain_size];
	float RiverModel[terrain_size][terrain_size];
	void CreateRiver(float terrain[terrain_size][terrain_size]);
	void RenderRiver(float terrain[terrain_size][terrain_size]);
	~River();
};

