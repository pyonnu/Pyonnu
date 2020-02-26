#pragma once
#define InventorySize 50
class Inventory
{
private:
	typedef map<string, Item*> mItem;
	typedef map<string, Item*>::iterator miItem;
private:
	Item* _item;
	vector<Item*> _vInven;
	vector<Item*>::iterator _viInven;
	

	mItem _mItem;
	miItem _miItem;

	image* _inventoryImage;
	image* _selectInventoryImage;
	image* _selectItemImage;
	image* _coinSlotImage;
	image* _armorSlotImage;
	RECT _slot[InventorySize];
	RECT _inventoryRect;

	int _selectQuickSlot;
	int _FilledInventory;
	bool _invenSee;
	bool _selectItem;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC dc);

	void InvenToryControl();
	void ItemAdd(string itemName, Item* item);
	void ItemSelect(int i,int j);

	Item* getItem() { return _vInven[_selectQuickSlot]; }
	type getSelectItem() {return _vInven[_selectQuickSlot]->getItemType(); }
	ItemType getSelectItemType1() { return _vInven[_selectQuickSlot]->getItemType1(); }
	ItemType getSelectItemType2() { return _vInven[_selectQuickSlot]->getItemType2(); }
	image* getSelectItemImage() { return _vInven[_selectQuickSlot]->getImage(); }
	bool getInvenSee() { return _invenSee; }
	RECT getInventoryRect() { return _inventoryRect; }
	
};

