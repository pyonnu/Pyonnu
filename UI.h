#pragma once
#include"gameNode.h"
#include"Inventory.h"
class UI:public gameNode
{
private:
	Inventory* _inventory;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

