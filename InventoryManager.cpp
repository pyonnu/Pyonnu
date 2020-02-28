#include "stdafx.h"
#include "InventoryManager.h"

HRESULT InventoryManager::init()
{
	_inventory = new Inventory;
	_inventory->init();
	return S_OK;
}

void InventoryManager::release()
{
}

void InventoryManager::update()
{
	_inventory->update();
}

void InventoryManager::render(HDC dc)
{
	_inventory->render(dc);
}

void InventoryManager::ItemAdd(string name, Item* item)
{
	_inventory->ItemAdd(name, item);
}

void InventoryManager::ItemAdd(string name, Item* item, int stack)
{
	_inventory->ItemAdd(name, item,stack);
}

Item* InventoryManager::findItem(string itemName)
{
	return _inventory->findItem(itemName);
}
