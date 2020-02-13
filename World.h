#pragma once
#include"gameNode.h"
#include"Player.h"
#include"EnemyManager.h"

class World :public gameNode
{
private:
	Player* _player;
	EnemyManager* _enemyManager;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

