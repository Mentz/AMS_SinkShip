#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "grid.hpp"

using namespace std;

class Enemy {
public:
	pair<int,int> play(Grid* campo){
		int x, y;
		do {
			x = rand() % TAM_CAMPO;
			y = rand() % TAM_CAMPO;
		} while(campo -> getCelula(make_pair(x, y)).getMorto());
		return make_pair(x, y);
	}
};

#endif