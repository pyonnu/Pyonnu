#include "stdafx.h"
#include "CraftingManager.h"

HRESULT CraftingManager::init()
{
	_crafting = new Crafting;
	_crafting->init();
	return S_OK;
}

void CraftingManager::release()
{
}

void CraftingManager::update()
{
	_crafting->update();
}

void CraftingManager::render(HDC dc)
{
	_crafting->render(dc);
}

void CraftingManager::ButtonClick()
{
	_crafting->ButtonClick();
}

void CraftingManager::setXY(float x, float y)
{
	_crafting->setXY(x, y);
}
