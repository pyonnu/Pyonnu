#pragma once
#include"singletonBase.h"
#include"Item.h"
#include<map>
class ItemManager:public singletonBase<ItemManager>
{
private:
	typedef map<string, Item*> mItem;
	typedef map<string, Item*>::iterator miItem;
private:
	mItem _mItem;
	miItem _miItem;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC dc);

	Item* itemAdd(string itemName, type type1, ItemType type2, string image, int stack);
	Item* itemAdd(string itemName, type type1, ItemType type2, ItemType type3, string image, int stack);
	Item* itemAdd(string itemName, type type1, ItemType type2, string image, int stack, float point);
								 
	Item* itemAdd(string itemName, type type1, ItemType type2, image* image, int stack);
	Item* itemAdd(string itemName, type type1, ItemType type2, ItemType type3,image* image, int stack);
	Item* itemAdd(string itemName, type type1, ItemType type2, image* image, int stack,float point);

	Item* findItem(string itemName);

	void CreateItem(string itemName,float x,float y);
};

