#pragma once
#include"gameNode.h"
struct enemyInfo
{
	int x, y;
};
class Enemy:public gameNode
{
protected:
	enemyInfo _enemyInfo;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void Move();

	virtual enemyInfo getEnemyInfo() { return _enemyInfo; }
};

