#pragma once
#include"gameNode.h"
#include"Player.h"
#include"Inventory.h"
class UI:public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

