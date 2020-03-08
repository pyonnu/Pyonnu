#pragma once
#include"gameNode.h"
#include"Player.h"
#include"EnemyManager.h"
#include"UI.h"
#include"Map.h"
class World :public gameNode
{
private:
	Map* _map;
	Player* _player;
	EnemyManager* _enemyManager;
	UI* _ui;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void collision();
	
};

