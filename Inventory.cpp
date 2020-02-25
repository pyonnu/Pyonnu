#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_vItem.resize(InventorySize);
	_inventoryImage = IMAGEMANAGER->findImage("Inventory_Back");
	_selectInventoryImage = IMAGEMANAGER->findImage("Inventory_Back14");
	
	_invenSee = false;
	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))_selectQuickSlot = 0;
	if (KEYMANAGER->isOnceKeyDown('2'))_selectQuickSlot = 1;
	if (KEYMANAGER->isOnceKeyDown('3'))_selectQuickSlot = 2;
	if (KEYMANAGER->isOnceKeyDown('4'))_selectQuickSlot = 3;
	if (KEYMANAGER->isOnceKeyDown('5'))_selectQuickSlot = 4;
	if (KEYMANAGER->isOnceKeyDown('6'))_selectQuickSlot = 5;
	if (KEYMANAGER->isOnceKeyDown('7'))_selectQuickSlot = 6;
	if (KEYMANAGER->isOnceKeyDown('8'))_selectQuickSlot = 7;
	if (KEYMANAGER->isOnceKeyDown('9'))_selectQuickSlot = 8;
	if (KEYMANAGER->isOnceKeyDown('0'))_selectQuickSlot = 9;
	if (KEYMANAGER->isToggleKey('I'))
	{
		_invenSee = true;
	}
	else
	{
		_invenSee = false;
	}
	Item* item;
	item = new Item;
	item = ITEMMANAGER->findItem("item_55");
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		
		_viItem = _vItem.begin();
		_viItem = _vItem.insert(_viItem, item);
		
	}
}

void Inventory::render()
{
	char str[256];
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	for (int i = 0;i < 10;i++)
	{
		_inventoryImage->render(getMemDC(), 20 + i * 62, 20);
		if (i == _selectQuickSlot && !_invenSee)_selectInventoryImage->render(getMemDC(), 15 + i * 62, 15);
	}
	if (_invenSee)
	{
		for (int x = 0;x < 10;x++)
		{
			for (int y = 0;y < 4;y++)
				_inventoryImage->render(getMemDC(), 20 + x * 62, 82 + y * 62);
		}
	}
	for (int x = 0;x < 10;x++)
	{
		for (int y = 0;y < 5;y++)
		{
			if (y < 1 || _invenSee)
			{
				if (_vItem[x + y * 10] == NULL)continue;
				_vItem[x + y * 10]->render(getMemDC(), 20 + x * 62, 20 + y * 62);
				sprintf_s(str, "%d", _vItem[x+y*10]->getItemStack());
				TextOut(getMemDC(), 20+x*62, 20+y*62, str, strlen(str));

				/*for (_viItem = _vItem.begin();_viItem != _vItem.end();++_viItem)
				{
					if (!(*_viItem) == NULL)
					{
						(*_viItem)->render(getMemDC(), 30+x*62,30+y*62);
					}
				}*/
				//_vItem[x + y * 10]->render(getMemDC(), 30 + x * 62, 30 + y * 62);
			}
		}
	}
}
