#include "SystemMniejszejRoslinnosci.h"

SystemMniejszejRoslinnosci::SystemMniejszejRoslinnosci(){
	
}


SystemMniejszejRoslinnosci::~SystemMniejszejRoslinnosci(){

}

void SystemMniejszejRoslinnosci::rysuj() {
	glColor3f(0.5, 0.5,0.01);
	for (int i = 0; i < roslinki.size(); i++){
		roslinki[i]->rysuj();
	}

	
}

void SystemMniejszejRoslinnosci::generuj(float terrain[terrain_size][terrain_size]) {
	for (int i = 0; i < 100; i++) {
		int x = rand() % 150;
		int z = rand() % 150;
		float * pozycjaTraw = new float[3];
		pozycjaTraw[0] = (x)*0.1f;
		pozycjaTraw[1] = terrain[x][z] * 0.1f - 0.01f;
		pozycjaTraw[2] = (z)*0.1f;
		this->roslinki.push_back(new MniejszaRoslinka(pozycjaTraw, losujTeksture(), ((rand() % 15 + 5) / 100.0f)));
	}

	for (int i = 0; i < 500; i++) {
		int x = rand() % 149+1;
		int z = rand() % 149+1;

		for (int i = 0; i < rand() % 20+10; i++) {
			float * pozycjaTraw = new float[3];

			int przesuniecieX = rand() % 14 - 7, przesuniecieZ = rand() % 14 - 7;

			pozycjaTraw[0] = (x + przesuniecieX)*0.1f ;
			pozycjaTraw[2] = (z + przesuniecieZ)*0.1f ;
			pozycjaTraw[1] = terrain[x+ przesuniecieX][z+ przesuniecieZ] * 0.1f - 0.01f;
			
			if (x + przesuniecieX > 1 && x + przesuniecieX<149 && z + przesuniecieZ > 1 && z + przesuniecieZ < 149) {
				this->roslinki.push_back(new MniejszaRoslinka(pozycjaTraw, losujTeksture(), ((rand() % 15 + 5) / 100.0f)));
			}
			
		}

	}
}

int SystemMniejszejRoslinnosci::losujTeksture() {
	GLuint tekstura;
	int prawdopodobienstwo = rand() % 100;
	if (prawdopodobienstwo < 4)
		tekstura = tekstury.tekstura(0);
	else if (prawdopodobienstwo < 50)
		tekstura = tekstury.tekstura(1);
	else
		tekstura = tekstury.tekstura(2);
	return tekstura;
}