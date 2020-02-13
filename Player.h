#pragma once
#include"gameNode.h"
#include"Item.h"

class EnemyManager;
struct PlayerInfo
{
	int idx, idy;
	float x, y;
	float speed;
	float damage;
	float Defense;

};
class Player :public gameNode
{
private:
	EnemyManager* _enemyManager;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemyManagerLink(EnemyManager* Link) { _enemyManager = Link; }

};
