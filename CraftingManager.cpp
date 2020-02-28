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
