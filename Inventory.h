#pragma once
#include"gameNode.h"
#define InventorySize 50
class Inventory :public gameNode
{
private:
	typedef map<string, Item*> mItem;
	typedef map<string, Item*>::iterator miItem;
private:
	Item* _item[InventorySize];
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;

	mItem _mItem;
	miItem _miItem;

	image* _inventoryImage;
	image* _selectInventoryImage;
	image* _coinSlotImage;
	image* _armorSlotImage;

	int _selectQuickSlot;

	bool _invenSee;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void InvenToryControl();

	type getSelectItem() { return _vItem[_selectQuickSlot]->getItemType(); }
	ItemType getSelectItemType1() { return _vItem[_selectQuickSlot]->getItemType1(); }
	ItemType getSelectItemType2() {return _vItem[_selectQuickSlot]->getItemType2();}
};

