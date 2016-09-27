#include "SystemDrzew.h"



SystemDrzew::SystemDrzew()
{


}


SystemDrzew::~SystemDrzew()
{
}

void SystemDrzew::generuj(float terrain[terrain_size][terrain_size], bool riverMask[terrain_size][terrain_size])
{
	srand((int)time(NULL));


	float pozycja2[3] = { 
		(terrain_size / 4)*0.1f,
		terrain[terrain_size / 4][terrain_size / 2]*0.1f - 0.01f,
		(terrain_size / 2)*0.1f 
	};
	drzewa.push_back(new Drzewo(pozycja2, Drzewo::ROZGALEZIONE));


	for (int i = 0; i < terrain_size/4; i++) {
		int x = rand() % (terrain_size);
		int z = rand() % (terrain_size);
		if (riverMask[x][z]) continue;
		float * pozycjaTraw = new float[3];
		pozycjaTraw[0] = (x)*0.1f;
		pozycjaTraw[1] = terrain[x][z] * 0.1f - 0.01f;
		pozycjaTraw[2] = (z)*0.1f;
		if (riverMask[(int)(x*0.1f)][(int)(z*0.1f)]) continue;
		drzewa.push_back(new Drzewo(pozycjaTraw, Drzewo::ROZGALEZIONE));
	}
}

void SystemDrzew::Rysuj()
{
	for (int i = 0; i < drzewa.size(); i++){
		drzewa[i]->Rysuj();
	}
}
