#pragma once
#include"gameNode.h"
#define InventorySize 50
class Inventory :public gameNode
{
private:
	Item* _item[InventorySize];
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;

	image* _inventoryImage;
	image* _coinSlotImage;
	image* _armorSlotImage;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

