#include "stdafx.h"
#include "UI.h"

HRESULT UI::init()
{
	INVENTORYMANAGER->init();
	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
	INVENTORYMANAGER->update();
}

void UI::render()
{
	INVENTORYMANAGER->render(getMemDC());
}
