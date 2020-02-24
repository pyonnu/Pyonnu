#include "stdafx.h"
#include "UI.h"

HRESULT UI::init()
{
	_inventory = new Inventory;
	_inventory->init();
	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
	_inventory->update();
}

void UI::render()
{
	_inventory->render();
}
