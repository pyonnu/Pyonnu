#pragma once
#include"gameNode.h"
#include"Demon.h"
#include"DemonEye.h"
#include"Slime.h"
#include"Zombie.h"
#include"EyeOfCthulhu.h"
#include"Item.h"
#include<vector>

class Player;

class EnemyManager:public gameNode
{
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

