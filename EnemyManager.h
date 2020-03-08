#pragma once
#include"gameNode.h"
#include"Demon.h"
#include"DemonEye.h"
#include"Slime.h"
#include"Zombie.h"
#include"EyeOfCthulhu.h"
#include"Item.h"
#include"Tile.h"
#include<vector>

class Player;

class EnemyManager:public gameNode
{
private:
	typedef vector<tagTile*> Tile;
	typedef vector<tagTile*>::iterator iTile;
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;
	Player* _player;
	float _spawnTimer;

	Tile _Tile;
	iTile _iTile;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyCreate();
	void SlimeCreate();
	void DemonEyeCreate();
	void DemonCreate();
	void ZombieCreate();
	void BossCreate();

	void collision();
	void LeftCollision(vector<Enemy*>::iterator viEnemy);
	void TopCollision(vector<Enemy*>::iterator viEnemy);
	void RightCollision(vector<Enemy*>::iterator viEnemy);
	void BottomCollision(vector<Enemy*>::iterator viEnemy);

	void enemyRemove();

	void PlayerLink(Player* Link) { _player = Link; }
	vector<Enemy*> getVEnemy() { return _vEnemy; }
	vector<Enemy*>::iterator getViEnemy() { return _viEnemy; }
	void setVTile(Tile tile) { _Tile = tile; }
	void setViTile(iTile iTile) { _iTile = iTile; }
};

