#pragma once
#include "Definicje.h"
#include <vector>
#include "GL/glew.h"
#include "Tekstury.h"
#include "MniejszaRoslinka.h"

using std::vector;
class SystemMniejszejRoslinnosci
{
	Tekstury tekstury;
	vector<MniejszaRoslinka*> roslinki;
	int losujTeksture();
public:
	SystemMniejszejRoslinnosci();
	~SystemMniejszejRoslinnosci();
	void rysuj();
	void generuj(float terrain[terrain_size][terrain_size], bool riverMask[terrain_size][terrain_size]);
};

