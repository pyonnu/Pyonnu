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
}

void ItemManager::render(HDC dc)
{
	for (_miItem = _mItem.begin();_miItem != _mItem.end();++_miItem)
	{
		_miItem->second->render(dc);
	}
}

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, string image, int stack)
{
	Item* item = findItem(itemName);

	//만약에 내가 찾으려던 아이템이 이미 등록되어있으면 걔를 반환
	if (item) return item;

	item = new Item;

	if (FAILED(item->init(type1, type2, image, stack)))
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

	if (FAILED(item->init(type1, type2, type3, image, stack)))
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

	if (FAILED(item->init(type1, type2, image, stack, point)))
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

	if (FAILED(item->init(type1, type2, image, stack)))
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

	if (FAILED(item->init(type1, type2,type3, image, stack)))
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

	if (FAILED(item->init(type1,type2,image,stack,point)))
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

	if (key != _mItem.end())
	{
		return key->second;
	}
	
	return nullptr;
}

void ItemManager::CreateItem(string itemName, float x, float y)
{
	//Item* item;
	//item = new Item;
	//item->CreateItem(x,y);
	findItem(itemName)->CreateItem(x, y);
}
