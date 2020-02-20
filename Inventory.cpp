#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_item = new Item;

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
}

void Inventory::render()
{
}
