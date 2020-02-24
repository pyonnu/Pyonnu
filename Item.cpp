#include "stdafx.h"
#include "Item.h"

HRESULT Item::init(type type1, ItemType type2, string image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = IMAGEMANAGER->findImage(image);
	_itemInfo->itemStack = stack;
	return S_OK;
}

HRESULT Item::init(type type1, ItemType type2, ItemType type3, string image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemType2 = type3;
	_itemInfo->itemImage = IMAGEMANAGER->findImage(image);
	_itemInfo->itemStack = stack;
	return S_OK;
}

HRESULT Item::init(type type1, ItemType type2, string image, int stack, float point)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = IMAGEMANAGER->findImage(image);
	_itemInfo->itemStack = stack;
	switch (type2)
	{
	case ItemType::BLOCK:
		break;
	case ItemType::WALL:
		break;
	case ItemType::METERIAL:
		break;
	case ItemType::CONSUMBLE:
		_itemInfo->PotionHealthPoint = point;
		break;
	case ItemType::PICKAXE:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::AXE:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::HAMMER:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::SWORD:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::ARMOR:
		_itemInfo->ArmorDefense = point;
		break;
	default:
		break;
	}
	return S_OK;
}

HRESULT Item::init(type type1, ItemType type2, image* image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = image;
	_itemInfo->itemStack = stack;
	return S_OK;
}

HRESULT Item::init(type type1, ItemType type2, ItemType type3, image* image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemType2 = type3;
	_itemInfo->itemImage = image;
	_itemInfo->itemStack = stack;
	return S_OK;
}

HRESULT Item::init(type type1, ItemType type2, image* image, int stack, float point)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = image;
	_itemInfo->itemStack = stack;
	switch (type2)
	{
	case ItemType::BLOCK:
		break;
	case ItemType::WALL:
		break;
	case ItemType::METERIAL:
		break;
	case ItemType::CONSUMBLE:
		_itemInfo->PotionHealthPoint = point;
		break;
	case ItemType::PICKAXE:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::AXE:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::HAMMER:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::SWORD:
		_itemInfo->weaponDamage = point;
		break;
	case ItemType::ARMOR:
		_itemInfo->ArmorDefense = point;
		break;
	default:
		break;
	}
	return S_OK;
}


void Item::release()
{
}

void Item::update()
{
}

void Item::render()
{
}

void Item::render(HDC dc)
{
	_itemInfo->itemImage->render(dc, 10, 10);
}

