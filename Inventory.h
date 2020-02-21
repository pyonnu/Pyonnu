#pragma once
#include"gameNode.h"
#include"Item.h"
#define InventorySize 50
class Inventory :public gameNode
{
private:
	ItemInfo* _itemInfo[InventorySize];
	Item* _item;
	vector<ItemInfo*> _vItemInfo;
	vector<ItemInfo*>::iterator _viItemInfo;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

