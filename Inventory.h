#pragma once
#include"gameNode.h"
#include"Item.h"
class Inventory :public gameNode
{
private:
	Item* _item;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

