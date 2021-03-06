#pragma once
#define InventorySize 50
class Inventory
{
private:
	typedef map<string, Item*> mItem;
	typedef map<string, Item*>::iterator miItem;
private:
	Item* _item;
	string _itemName[InventorySize];
	string _name;
	vector<Item*> _vInven;
	vector<Item*>::iterator _viInven;
	

	mItem _mItem;
	miItem _miItem;

	image* _inventoryImage;
	image* _selectInventoryImage;
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

	void InvenToryControl(HDC dc);
	void setItem(Item* item) { _item = item; }
	void ItemAdd(string itemName, Item* item);
	void ItemAdd(string itemName, Item* item,int stack);
	void ItemSelect(int i,int j);

	Item* getItem() { return _vInven[_selectQuickSlot]; }
	type getSelectItem() {return _vInven[_selectQuickSlot]->getItemType(); }
	ItemType getSelectItemType1() { return _vInven[_selectQuickSlot]->getItemType1(); }
	ItemType getSelectItemType2() { return _vInven[_selectQuickSlot]->getItemType2(); }
	image* getSelectItemImage() { return _vInven[_selectQuickSlot]->getImage(); }
	bool getInvenSee() { return _invenSee; }
	RECT getInventoryRect() { return _inventoryRect; }
	
	mItem getMItem() { return _mItem; }
	Item* findItem(string itemName);
};

