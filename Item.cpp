#include "stdafx.h"
#include "Item.h"

HRESULT Item::init(float x, float y, type type1, ItemType type2, string image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = IMAGEMANAGER->findImage(image);
	_itemInfo->itemStack = stack;
	_itemInfo->rc = RectMake(x + _itemInfo->itemImage->getWidth() / 2, y + _itemInfo->itemImage->getHeight() / 2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
	return S_OK;
}

HRESULT Item::init(float x, float y, type type1, ItemType type2, ItemType type3, string image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemType2 = type3;
	_itemInfo->itemImage = IMAGEMANAGER->findImage(image);
	_itemInfo->itemStack = stack;
	_itemInfo->rc = RectMake(x + _itemInfo->itemImage->getWidth() / 2, y + _itemInfo->itemImage->getHeight() / 2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
	return S_OK;
}

HRESULT Item::init(float x, float y, type type1, ItemType type2, string image, int stack, float point)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = IMAGEMANAGER->findImage(image);
	_itemInfo->itemStack = stack;
	_itemInfo->rc = RectMake(x + _itemInfo->itemImage->getWidth() / 2, y + _itemInfo->itemImage->getHeight() / 2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
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

HRESULT Item::init(float x, float y, type type1, ItemType type2, string image, float point)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = IMAGEMANAGER->findImage(image);
	_itemInfo->rc = RectMake(x + _itemInfo->itemImage->getWidth() / 2, y + _itemInfo->itemImage->getHeight() / 2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
	switch (type2)
	{
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
	}
	return S_OK;
	return S_OK;
}

HRESULT Item::init(float x, float y, type type1, ItemType type2, image* image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = image;
	_itemInfo->itemStack = stack;
	_itemInfo->rc = RectMake(x + _itemInfo->itemImage->getWidth() / 2, y + _itemInfo->itemImage->getHeight() / 2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
	return S_OK;
}

HRESULT Item::init(float x, float y, type type1, ItemType type2, ItemType type3, image* image, int stack)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemType2 = type3;
	_itemInfo->itemImage = image;
	_itemInfo->itemStack = stack;
	_itemInfo->rc = RectMake(x + _itemInfo->itemImage->getWidth() / 2, y + _itemInfo->itemImage->getHeight() / 2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
	return S_OK;
}

HRESULT Item::init(float x, float y, type type1, ItemType type2, image* image, int stack, float point)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = image;
	_itemInfo->itemStack = stack;
	_itemInfo->rc = RectMake(x+_itemInfo->itemImage->getWidth()/2, y+_itemInfo->itemImage->getHeight()/2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
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
	}
	return S_OK;
}

HRESULT Item::init(float x, float y, type type1, ItemType type2, image* image, float point)
{
	_itemInfo = new tagItemInfo;
	_itemInfo->Type = type1;
	_itemInfo->itemType = type2;
	_itemInfo->itemImage = image;
	_itemInfo->rc = RectMake(x+_itemInfo->itemImage->getWidth()/2, y+_itemInfo->itemImage->getHeight()/2, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(0);
	switch (type2)
	{
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
	}
	return S_OK;
}


void Item::release()
{
}

void Item::update()
{
	
}

void Item::render(HDC dc)
{
	if (_itemInfo->itemType == ItemType::PICKAXE || _itemInfo->itemType == ItemType::AXE || _itemInfo->itemType == ItemType::HAMMER || _itemInfo->itemType == ItemType::SWORD)
		_itemInfo->itemImage->rotateRender(dc, _itemInfo->rc.left, _itemInfo->rc.top, _itemInfo->itemImage->getRotationAngle() - 0.1f);
	else
	{
		_itemInfo->itemImage->render(dc, _itemInfo->rc.left-_itemInfo->itemImage->getWidth()/2, _itemInfo->rc.top- _itemInfo->itemImage->getHeight()/ 2);
	}
}

void Item::render(HDC dc,float x,float y)
{
	_itemInfo->itemImage->render(dc, x, y);
}

void Item::CreateItem(float x, float y)
{
	_itemInfo->rc = RectMake(x, y, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
	_itemInfo->itemImage->setRotationAngle(PI / 2);
}

void Item::CreateItem(string itemName, float x, float y)
{
	_itemInfo->itemImage = IMAGEMANAGER->findImage(itemName);
	_itemInfo->itemImage->setRotationAngle(PI / 2);
	_itemInfo->rc = RectMake(x, y, _itemInfo->itemImage->getWidth(), _itemInfo->itemImage->getHeight());
}