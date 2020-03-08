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
	char Hp[1000];
	char MaxHp[1000];
	char defense[1000];
	INVENTORYMANAGER->render(getMemDC());
	CRAFTINGMANAGER->render(getMemDC());
	for (int i = 0;i < _HP / 20;i++)
	{
		IMAGEMANAGER->findImage("Heart")->render(getMemDC(), WINSIZEX - 220 + i * 44, 20);
	}
	if (INVENTORYMANAGER->getInvenSee())
	{
		sprintf_s(defense, "%.0f", _Defense);
		//TextOut(getMemDC(), , , );
	}
	sprintf_s(Hp, "%.0f", _HP);
	TextOut(getMemDC(), WINSIZEX - 140, 0, Hp, strlen(Hp));
	TextOut(getMemDC(), WINSIZEX - 110, 0, "/", strlen("/"));
	sprintf_s(MaxHp, "%.0f", _MaxHP);
	TextOut(getMemDC(), WINSIZEX - 100, 0, MaxHp, strlen(MaxHp));

}