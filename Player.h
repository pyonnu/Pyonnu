#pragma once
#include"gameNode.h"
#include"Item.h"

class EnemyManager;

class Player :public gameNode
{
private:
public:
	HRESULT init();
	void release();
	void update();
	void render();
};
