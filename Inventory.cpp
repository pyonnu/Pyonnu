#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_vInven.resize(InventorySize);
	_inventoryImage = IMAGEMANAGER->findImage("Inventory_Back");
	_selectInventoryImage = IMAGEMANAGER->findImage("Inventory_Back14");
	_selectQuickSlot = _FilledInventory = 0;
	_invenSee = false;
	_inventoryRect = RectMake(0, 0, 20 + 62 * 10, 20 + 62 * 5);
	for (int i = 0; i < 10;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			_slot[i + j * 10] = RectMake(20 + i * 62, 20 + j * 62, 52, 52);
		}
	}
	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	//InvenToryControl(dc);
	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (_vInven[i + j * 10] != NULL)
				if (_vInven[i + j * 10]->getItemStack() <= 0)
				{
					_mItem.erase(_itemName[i + j * 10]);
					_vInven[i + j * 10] = NULL;
				}
		}
	}
	CRAFTINGMANAGER->InvenSee(_invenSee);
}

void Inventory::render(HDC dc)
{
	char str[256];
	SetTextColor(dc, RGB(255, 255, 255));
	SetBkMode(dc, TRANSPARENT);
	for (int i = 0;i < 10;i++)
	{
		_inventoryImage->render(dc, 20 + i * 62, 20);
		if (i == _selectQuickSlot && !_invenSee)_selectInventoryImage->render(dc, 15 + i * 62, 15);
	}
	if (_invenSee)
	{
		for (int x = 0;x < 10;x++)
		{
			for (int y = 0;y < 5;y++)
			{
				_inventoryImage->render(dc, 20 + x * 62, 20 + y * 62);
			}


		}
	}
	for (int x = 0;x < 10;x++)
	{
		for (int y = 0;y < 5;y++)
		{
			if (y < 1 || _invenSee)
			{
				if (_vInven[x + y * 10] == NULL)continue;
				_vInven[x + y * 10]->render(dc, 20 + x * 62, 20 + y * 62);
				if (_vInven[x + y * 10]->getItemType1() == ItemType::ARMOR
					|| _vInven[x + y * 10]->getItemType1() == ItemType::HELMET
					|| _vInven[x + y * 10]->getItemType1() == ItemType::LEGGINGS
					|| _vInven[x + y * 10]->getItemType1() == ItemType::PICKAXE
					|| _vInven[x + y * 10]->getItemType1() == ItemType::AXE
					|| _vInven[x + y * 10]->getItemType1() == ItemType::HAMMER
					|| _vInven[x + y * 10]->getItemType1() == ItemType::SWORD)
				{

				}
				else
				{
					sprintf_s(str, "%d", _vInven[x + y * 10]->getItemStack());
					TextOut(dc, 20 + x * 62, 20 + y * 62, str, strlen(str));
				}

			}
		}
	}
	if (_selectItem)_item->getImage()->render(dc, _ptMouse.x, _ptMouse.y);
	//Rectangle(dc, _inventoryRect);
	InvenToryControl(dc);
}

void Inventory::InvenToryControl(HDC dc)
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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_invenSee)
		{
			CRAFTINGMANAGER->ButtonClick();
			for (int i = 0;i < 10;i++)
			{
				for (int j = 0;j < 5;j++)
				{
					if (PtInRect(&_slot[i + j * 10], _ptMouse))
					{
						ItemSelect(i, j);
					}
				}
			}

		}
	}


}

void Inventory::ItemAdd(string itemName, Item* item)
{
	miItem key = _mItem.find(itemName);
	if (key != _mItem.end())
	{
		_mItem.find(itemName)->second->PlusItemStack();
		cout << 28 << endl;
	}
	else
	{
		for (int i = 0;i < InventorySize;i++)
		{
			if (_vInven[i] == NULL)
			{
				_vInven[i] = item;
				_itemName[i] = itemName;
				_mItem.insert(make_pair(itemName, item));
				break;
			}
		}
		cout << 38 << endl;
	}

}

void Inventory::ItemAdd(string itemName, Item* item, int stack)
{
	miItem key = _mItem.find(itemName);

	if (key != _mItem.end())
	{
		_mItem.find(itemName)->second->AddItemStack(stack);
		cout << 28 << endl;
	}
	else
	{
		for (int i = 0;i < InventorySize;i++)
		{
			if (_vInven[i] == NULL)
			{
				_vInven[i] = item;
				_itemName[i] = itemName;
				_mItem.insert(make_pair(itemName, item));
				break;
			}
		}
		cout << 38 << endl;
	}
}

void Inventory::ItemSelect(int i, int j)
{
	if (!_selectItem)
	{
		if (_vInven[i + j * 10] == NULL)return;
		_name = _itemName[i + j * 10];
		_itemName[i + j * 10].clear();
		_item = _vInven[i + j * 10];
		_vInven[i + j * 10] = NULL;
		_selectItem = true;
	}
	else if (_selectItem)
	{
		if (_vInven[i + j * 10] != NULL)return;
		_vInven[i + j * 10] = _item;
		_itemName[i + j * 10] = _name;
		_name.clear();
		_item = NULL;
		_selectItem = false;
	}
}

Item* Inventory::findItem(string itemName)
{
	miItem key = _mItem.find(itemName);

	if (key != _mItem.end())
	{
		return key->second;
	}

	return nullptr;
}
