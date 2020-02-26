#pragma once
#include"singletonBase.h"
#include"Inventory.h"
class InventoryManager:public singletonBase<InventoryManager>
{
private:
	Inventory* _inventory;
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;

	vector<Item*> _vInven;
	vector<Item*>::iterator _viInven;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC dc);

	void ItemAdd(string name, Item* item);

	Item* getItem() { return _inventory->getItem(); }
	bool getInvenSee() { return _inventory->getInvenSee(); }
	RECT getRect() { return _inventory->getInventoryRect(); }
	type getitem() { return _inventory->getSelectItem(); }
	ItemType getItemType1() { return _inventory->getSelectItemType1(); }
	ItemType getitemType2() { return _inventory->getSelectItemType2(); }
	image* getImage() { return _inventory->getSelectItemImage(); }
};

