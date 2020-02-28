#include "stdafx.h"
#include "Crafting.h"

HRESULT Crafting::init()
{
	_craftPage = 1;
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			_craftRect1[i + j * 5] = RectMake(330+i*62,392+j*62,52,52);
			//_craftRect2[i + j * 5] = RectMake();
			//_craftRect3[i + j * 5] = RectMake();
		}
	}
	for (int i = 0;i < MaxItem;i++)
	{
		_craftRect4[i] = RectMake(20, 392 + i * 62, 52, 52);
	}
	a = 0;
	return S_OK;
}

void Crafting::release()
{
}

void Crafting::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		a--;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		a++;
	}
	for (int i = 0;i < MaxItem;i++)
	{
		_craftRect4[i] = RectMake(20, 392 + (i + a) * 62, 52, 52);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_craftRect4[i], _ptMouse))
		{
			
		}
	}
	
}

void Crafting::render(HDC dc)
{
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (_craftPage == 1)
			{
				Rectangle(dc, _craftRect1[i + j * 5]);
			}
			if (_craftPage == 2)
			{
				Rectangle(dc, _craftRect2[i + j * 5]);
			}
			if (_craftPage == 3)
			{
				Rectangle(dc, _craftRect3[i + j * 5]);
			}
		}
	}
	for (int i = 0;i < MaxItem;i++)
	{
		Rectangle(dc, _craftRect4[i]);
	}
}
