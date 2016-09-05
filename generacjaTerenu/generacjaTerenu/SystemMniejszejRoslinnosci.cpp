#include "SystemMniejszejRoslinnosci.h"

SystemMniejszejRoslinnosci::SystemMniejszejRoslinnosci(){
	
}


SystemMniejszejRoslinnosci::~SystemMniejszejRoslinnosci(){

}

void SystemMniejszejRoslinnosci::rysuj() {
	for (int i = 0; i < roslinki.size(); i++){
		roslinki[i]->rysuj();
	}

	
}

void SystemMniejszejRoslinnosci::generuj(float terrain[terrain_size][terrain_size]) {
	for (int i = 0; i < 15000; i++){
		int x = rand() % 150;
		int z = rand() % 150;
		float * pozycjaTraw = new float[3];
		pozycjaTraw[0] = (x)*0.1f;
		pozycjaTraw[1] = terrain[x][z] * 0.1f - 0.01f;
		pozycjaTraw[2] = (z)*0.1f;
		GLuint tekstura ;
		int prawdopodobienstwo = rand() % 100;
			if(prawdopodobienstwo < 4)
				tekstura = tekstury.tekstura(0);
			else if (prawdopodobienstwo < 50)
				tekstura = tekstury.tekstura(1);
			else
				tekstura = tekstury.tekstura(2);
				

		this->roslinki.push_back(new MniejszaRoslinka(pozycjaTraw, tekstura, ((rand() % 15+5)/100.0f)));
	}
}
