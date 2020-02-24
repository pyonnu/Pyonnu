#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_inventoryImage = IMAGEMANAGER->findImage("Inventory_Back");

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_inventoryImage = IMAGEMANAGER->findImage("Inventory_Back14");
	}
}

void Inventory::render()
{
	for (int i = 0;i < 10;i++)
	{
		_inventoryImage->render(getMemDC(), 20 + i * 62, 20);
	}
	
}
