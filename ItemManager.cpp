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
	//cout << _vItem.size() << endl;
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

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, string image, int stack)
{
	Item* item = findItem(itemName);

	//���࿡ ���� ã������ �������� �̹� ��ϵǾ������� �¸� ��ȯ
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

	//���࿡ ���� ã������ �������� �̹� ��ϵǾ������� �¸� ��ȯ
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

	//���࿡ ���� ã������ �������� �̹� ��ϵǾ������� �¸� ��ȯ
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

Item* ItemManager::itemAdd(string itemName, type type1, ItemType type2, image* image, int stack)
{
	Item* item = findItem(itemName);

	//���࿡ ���� ã������ �������� �̹� ��ϵǾ������� �¸� ��ȯ
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

	//���࿡ ���� ã������ �������� �̹� ��ϵǾ������� �¸� ��ȯ
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

	//���࿡ ���� ã������ �������� �̹� ��ϵǾ������� �¸� ��ȯ
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