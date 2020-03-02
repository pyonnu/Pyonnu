#include "stdafx.h"
#include "ItemManager.h"

HRESULT ItemManager::init()
{
	return S_OK;
}

void ItemManager::release()
{
}

void ItemManager::update()
{
	for (_viItem = _vItem.begin();_viItem != _vItem.end();++_viItem)
	{
		(*_viItem)->update();
	}
}

void ItemManager::render(HDC dc)
{
	/*for (_miItem = _mItem.begin();_miItem != _mItem.end();++_miItem)
	{
		_miItem->second->render(dc);
	}*/
	for (_viItem = _vItem.begin();_viItem!=_vItem.end();++_viItem)
	{
		(*_viItem)->render(dc);
	}
}

void ItemManager::render(HDC dc, float x, float y)
{
	for (_viItem = _vItem.begin();_viItem != _vItem.end();++_viItem)
	{
		(*_viItem)->render(dc, x, y);
	}
}

void ItemManager::render(HDC dc, float x, float y,float angle)
{
	for (_viItem = _vItem.begin();_viItem != _vItem.end();++_viItem)
	{
		(*_viItem)->render(dc, x, y,angle);
	}
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, string image, int stack)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0,0,type1, type2, image, stack)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, ItemType type3, string image, int stack)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2, type3, image, stack)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, string image, int stack, float point)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2, image, stack, point)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, string image,  float point, float criticalChance)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2, image, point,criticalChance)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, string image,float point, float criticalChance, float toolsPower)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2, image, point, criticalChance,toolsPower)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, image* image, int stack)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2, image, stack)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, ItemType type3, image* image, int stack)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2,type3, image, stack)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, image* image, int stack,float point)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1,type2,image,stack,point)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, image* image,float point, float criticalChance)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2, image, point,criticalChance)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, image* image,float point, float criticalChance, float toolsPower)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(0, 0, type1, type2, image, criticalChance,toolsPower)))
	{
		SAFE_DELETE(item);

		return nullptr;
	}

	_mItem.insert(make_pair(itemName, item));

	return item;
}

Item* ItemManager::findItem(string itemName)
{
	miItem key = _mItem.find(itemName);
	cout << 7777777777 << endl;
	if (key != _mItem.end())
	{
		return key->second;
		cout << 999999 << endl;
	}
	
	return nullptr;
}

void ItemManager::CreateItem(string itemName, float x, float y)
{
	//Item* item;
	//item = new Item;
	//item = findItem(itemName);
	////findItem(itemName)->CreateItem(x, y);
	//item->CreateItem(x, y);
	//_vItem.push_back(item);

	////Item* item;
	////item = new Item;
	//////item = findItem(itemName);
	////item->CreateItem(itemName, x, y);
	////_vItem.push_back(item);
}

void ItemManager::CreateItem(float x,float y,type type1, ItemType type2, image* image, int stack)
{
	Item* item;
	item = new Item;
	item->init(x,y,type1, type2, image, stack);
	_vItem.push_back(item);
}

void ItemManager::CreateItem(float x, float y, type type1, ItemType type2, ItemType type3, image* image, int stack)
{
	Item* item;
	item = new Item;
	item->init(x,y,type1, type2, type3, image, stack);
	_vItem.push_back(item);
}

void ItemManager::CreateItem(float x, float y, type type1, ItemType type2, image* image, int stack, float point)
{
	Item* item;
	item = new Item;
	item->init(x, y, type1, type2, image, stack, point);
	_vItem.push_back(item);
}

void ItemManager::CreateItem(float x, float y, type type1, ItemType type2, image* image, float point)
{
	Item* item;
	item = new Item;
	item->init(x, y, type1, type2, image, point);
	_vItem.push_back(item);
}

void ItemManager::CreateItem(float x, float y, type type1, ItemType type2, image* image, float point, float critlcalChance)
{
	Item* item;
	item = new Item;
	item->init(x, y, type1, type2, image,critlcalChance);
	_vItem.push_back(item);
}

void ItemManager::CreateItem(float x, float y, type type1, ItemType type2, image* image, float point, float critlcalChance, float toolsPower)
{
	Item* item;
	item = new Item;
	item->init(x, y, type1, type2, image, point,critlcalChance,toolsPower);
	_vItem.push_back(item);
}
