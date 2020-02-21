#pragma once
#include"gameNode.h"
#include"Item.h"
class Crafting :public gameNode
{
private:
	Item* _item;
	item _itemType;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

