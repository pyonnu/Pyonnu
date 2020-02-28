#include "stdafx.h"
#include "UI.h"

HRESULT UI::init()
{
	INVENTORYMANAGER->init();
	CRAFTINGMANAGER->init();
	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
	INVENTORYMANAGER->update();
	CRAFTINGMANAGER->update();
}

void UI::render()
{
	INVENTORYMANAGER->render(getMemDC());
	CRAFTINGMANAGER->render(getMemDC());
}
