#pragma once
#include "Drzewo.h"
#include "Definicje.h"
#include <vector>
class SystemDrzew
{
	vector<Drzewo *> drzewa;
public:
	SystemDrzew();
	~SystemDrzew();
	void generuj(float terrain[terrain_size][terrain_size], bool RiverMask[terrain_size][terrain_size]);
	void Rysuj();
};

