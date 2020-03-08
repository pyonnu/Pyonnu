#include "stdafx.h"
#include "Crafting.h"

HRESULT Crafting::init()
{
	string str = "Item_";
	_craftPage = 1;
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			_craftRect1[i + j * 5] = RectMake(330 + i * 62, 392 + j * 62, 52, 52);
			_craftRect2[i + j * 5] = RectMake(330 + i * 62, 392 + j * 62, 52, 52);
			_craftRect3[i + j * 5] = RectMake(330 + i * 62, 392 + j * 62, 52, 52);
			if (i + j * 5 > 8)continue;
			_craftRect4[i + j * 5] = RectMake(330 + i * 62, 392 + j * 62, 52, 52);
		}
	}
	for (int i = 1;i < MaxItem;i++)
	{
		str = "Item_" + to_string(i);
		_scrollRect[i] = RectMake(20, 392 + i * 62, 52, 52);
		_showCraftImage[i] = IMAGEMANAGER->findImage(str);
		cout << str << endl;
	}
	_UpDownButton[0] = RectMake(300, 486, 20, 20);
	_UpDownButton[1] = RectMake(300, 516, 20, 20);
	_showCraft = RectMake(20, 392, 52, 300);
	_showRecipe = RectMake(82+20, 392 + 62 * 4, 30, 30);
	_craftNum = 1;
	_showRecipeList = false;
	_invenSee = false;
	for (int i = 0;i < 4;i++)
	{
		_CraftUIPos[i] = RectMake(20 + 62, 392 + i * 62, 52, 52);
	}
	_CraftShow = 0;
	return S_OK;
}

void Crafting::release()
{
}

void Crafting::update()
{
	if (_invenSee)
	{
		CraftingControl();
	}
}

void Crafting::render(HDC dc)
{
	if (_invenSee) draw(dc);
}

void Crafting::draw(HDC dc)
{
	RECT temp;
	if (_showRecipeList)
	{
		//Rectangle(dc, _UpDownButton[0]);
		TextOut(dc, _UpDownButton[0].left, _UpDownButton[0].top, "▲", strlen("▲"));
		//Rectangle(dc, _UpDownButton[1]);
		TextOut(dc, _UpDownButton[1].left, _UpDownButton[1].top, "▼", strlen("▼"));
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 4;j++)
			{

				if (_craftPage == 1)
				{
					Rectangle(dc, _craftRect1[i + j * 5]);
					_showCraftImage[i + j * 5 + 1]->render(dc, _craftRect1[i + j * 5].left, _craftRect1[i + j * 5].top);
				}
				if (_craftPage == 2)
				{
					Rectangle(dc, _craftRect2[i + j * 5]);
					_showCraftImage[i + j * 5 + 20 + 1]->render(dc, _craftRect2[i + j * 5].left, _craftRect2[i + j * 5].top);
				}
				if (_craftPage == 3)
				{
					Rectangle(dc, _craftRect3[i + j * 5]);
					_showCraftImage[i + j * 5 + 40 + 1]->render(dc, _craftRect3[i + j * 5].left, _craftRect3[i + j * 5].top);
				}
				if (_craftPage == 4)
				{
					if (i + j * 5 > 8)break;
					Rectangle(dc, _craftRect4[i + j * 5]);
					_showCraftImage[i + j * 5 + 60 + 1]->render(dc, _craftRect4[i + j * 5].left, _craftRect4[i + j * 5].top);
				}
			}
		}
	}
	for (int i = 1;i < MaxItem;i++)
	{
		if (IntersectRect(&temp, &_scrollRect[i], &_showCraft))
		{
			//Rectangle(dc, _scrollRect[i]);
			_showCraftImage[i]->render(dc, _scrollRect[i].left, _scrollRect[i].top);
		}

	}
	for (int i = 0;i < 4;i++)
	{
		//Rectangle(dc, _CraftUIPos[i]);
	}
	TextOut(dc, _CraftUIPos[0].left+20, _CraftUIPos[0].top,"재료",strlen("재료"));
	CraftingDraw(dc);
	TextOut(dc, _CraftUIPos[3].left + 20, _CraftUIPos[3].top,"제작",strlen("제작"));
	IMAGEMANAGER->findImage("Craft_Toggle_0")->render(dc, _showRecipe.left, _showRecipe.top);
}

void Crafting::CraftingDraw(HDC dc)
{
	if (_CraftShow == 1)
	{
		IMAGEMANAGER->findImage("Item_68")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "4", strlen("4"));
	}
	if (_CraftShow == 2)
	{
		IMAGEMANAGER->findImage("Item_69")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "4", strlen("4"));
	}
	if (_CraftShow == 3)
	{
		IMAGEMANAGER->findImage("Item_60")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "4", strlen("4"));
	}
	if (_CraftShow ==8 )
	{
		IMAGEMANAGER->findImage("Item_4")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
	}
	if (_CraftShow == 9)
	{
		IMAGEMANAGER->findImage("Item_5")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
	}
	if (_CraftShow ==10 )
	{
		IMAGEMANAGER->findImage("Item_6")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
	}
	if (_CraftShow == 11)
	{
		IMAGEMANAGER->findImage("Item_7")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
	}
	if (_CraftShow == 13)
	{
		IMAGEMANAGER->findImage("Item_12")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
	}
	if (_CraftShow == 14)
	{
		IMAGEMANAGER->findImage("Item_8")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 15)
	{
		IMAGEMANAGER->findImage("Item_8")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 16)
	{
		IMAGEMANAGER->findImage("Item_8")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 17)
	{
		IMAGEMANAGER->findImage("Item_8")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 18)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 19)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 20)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 21)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 22)
	{
		IMAGEMANAGER->findImage("Item_10")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 23)
	{
		IMAGEMANAGER->findImage("Item_10")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 24)
	{
		IMAGEMANAGER->findImage("Item_10")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 25)
	{
		IMAGEMANAGER->findImage("Item_10")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 26)
	{
		IMAGEMANAGER->findImage("Item_11")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 27)
	{
		IMAGEMANAGER->findImage("Item_11")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 28)
	{
		IMAGEMANAGER->findImage("Item_11")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 29)
	{
		IMAGEMANAGER->findImage("Item_11")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 30)
	{
		IMAGEMANAGER->findImage("Item_13")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 31)
	{
		IMAGEMANAGER->findImage("Item_13")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 32)
	{
		IMAGEMANAGER->findImage("Item_13")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 33)
	{
		IMAGEMANAGER->findImage("Item_13")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].bottom, "3", strlen("3"));
	}
	if (_CraftShow == 34)
	{
		IMAGEMANAGER->findImage("Item_8")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 35)
	{
		IMAGEMANAGER->findImage("Item_8")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 36)
	{
		IMAGEMANAGER->findImage("Item_8")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 37)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 38)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 39)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 40)
	{
		IMAGEMANAGER->findImage("Item_10")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 41)
	{
		IMAGEMANAGER->findImage("Item_10")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 42)
	{
		IMAGEMANAGER->findImage("Item_10")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 43)
	{
		IMAGEMANAGER->findImage("Item_11")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 44)
	{
		IMAGEMANAGER->findImage("Item_11")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 45)
	{
		IMAGEMANAGER->findImage("Item_11")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 46)
	{
		IMAGEMANAGER->findImage("Item_13")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 47)
	{
		IMAGEMANAGER->findImage("Item_13")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 48)
	{
		IMAGEMANAGER->findImage("Item_13")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 53)
	{
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 54)
	{
		IMAGEMANAGER->findImage("Item_2")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "10", strlen("10"));
	}
	if (_CraftShow == 55)
	{
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "8", strlen("8"));
	}
	if (_CraftShow == 56)
	{
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "8", strlen("8"));
	}
	if (_CraftShow == 57)
	{
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "5", strlen("5"));
	}
	if (_CraftShow == 58)
	{
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "8", strlen("8"));
		IMAGEMANAGER->findImage("Item_9")->render(dc, _CraftUIPos[1].left + 72, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left +72, _CraftUIPos[1].bottom, "5", strlen("5"));
	}
	if (_CraftShow == 59)
	{
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "6", strlen("6"));
	}
	if (_CraftShow == 60)
	{
		IMAGEMANAGER->findImage("Item_3")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "1", strlen("1"));
	}
	if (_CraftShow == 63)
	{
		IMAGEMANAGER->findImage("Item_62")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "6", strlen("6"));
	}
	if (_CraftShow == 68)
	{
		IMAGEMANAGER->findImage("Item_1")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "1", strlen("1"));
	}
	if (_CraftShow == 69)
	{
		IMAGEMANAGER->findImage("Item_2")->render(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].top);
		TextOut(dc, _CraftUIPos[1].left + 10, _CraftUIPos[1].bottom, "1", strlen("1"));
	}
}

void Crafting::CraftingControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_craftNum < 2)return;
		_craftNum--;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_craftNum > MaxItem - 6)return;
		_craftNum++;
	}
	for (int i = 1;i < MaxItem;i++)
	{
		_scrollRect[i] = RectMake(20, 392 + (i + -_craftNum) * 62, 52, 52);
	}
}

void Crafting::ButtonClick()
{
	if (PtInRect(&_showRecipe, _ptMouse))
	{
		if (_showRecipeList)_showRecipeList = false;
		else _showRecipeList = true;
	}
	if (PtInRect(&_UpDownButton[0], _ptMouse))
	{
		if (_craftPage > 1)
			_craftPage--;
	}
	if (PtInRect(&_UpDownButton[1], _ptMouse))
	{
		if (_craftPage < 4)
			_craftPage++;
	}
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (_craftPage == 1)
			{
				if (PtInRect(&_craftRect1[i + j * 5], _ptMouse))_craftNum = i + j * 5 + 1;
			}
			if (_craftPage == 2)
			{
				if (PtInRect(&_craftRect2[i + j * 5], _ptMouse))_craftNum = i + j * 5 + 21;
			}
			if (_craftPage == 3)
			{
				if (PtInRect(&_craftRect3[i + j * 5], _ptMouse))_craftNum = i + j * 5 + 41;
			}
			if (_craftPage == 4)
			{
				if (PtInRect(&_craftRect4[i + j * 5], _ptMouse))_craftNum = i + j * 5 + 61;
			}
		}
	}
	if (PtInRect(&_CraftUIPos[3], _ptMouse))
	{
		if (_CraftShow == 1)
		{
			if (INVENTORYMANAGER->findItem("item_68") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_68")->getItemStack() >= 4)
				{
					INVENTORYMANAGER->findItem("item_68")->removeItemStack(4);
					ITEMMANAGER->CreateItem(_x, _y, type::DIRT_BLOCK, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_1"), 1, 0);
				}
			}
		}

		if (_CraftShow == 2)
		{
			if (INVENTORYMANAGER->findItem("item_69") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_69")->getItemStack() >= 4)
				{
					INVENTORYMANAGER->findItem("item_69")->removeItemStack(4);
					ITEMMANAGER->CreateItem(_x, _y, type::STONE_BLOCK, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_2"), 1, 0);
				}
			}
		}

		if (_CraftShow == 3)
		{
			if (INVENTORYMANAGER->findItem("item_60") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_60")->getItemStack() >= 4)
				{
					INVENTORYMANAGER->findItem("item_60")->removeItemStack(4);
					ITEMMANAGER->CreateItem(_x, _y, type::WOOD, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_3"), 1, 0);
				}
			}
		}

		if (_CraftShow == 4)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x, _y, type::COPPER, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_4"), 5, 0);
				}
			}
		}

		if (_CraftShow == 5)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x, _y, type::IRON, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_5"), 5, 0);
				}
			}
		}

		if (_CraftShow == 6)
		{
			if (INVENTORYMANAGER->findItem("item_10") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_10")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_10")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x, _y, type::GOLD, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_6"), 5, 0);
				}
			}
		}

		if (_CraftShow == 7)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x, _y, type::PLATINUM, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_7"), 5, 0);
				}
			}
		}

		if (_CraftShow == 8)
		{

			if (INVENTORYMANAGER->findItem("item_4") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_4")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_4")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::COPPER_BAR, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_8"), 1, 0);
				}
			}
		}
		if (_CraftShow == 9)
		{
			if (INVENTORYMANAGER->findItem("item_5") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_5")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_5")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::IRON_BAR, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_9"), 1, 0);
				}
			}
		}
		if (_CraftShow == 10)
		{
			if (INVENTORYMANAGER->findItem("item_6") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_6")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_6")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::GOLD_BAR, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_10"), 1, 0);
				}
			}
		}

		if (_CraftShow == 11)
		{
			if (INVENTORYMANAGER->findItem("item_7") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_7")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_7")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::PLATINUM_BAR, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_11"), 1, 0);
				}
			}
		}
		if (_CraftShow == 12)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x, _y, type::DEMONITE, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_12"), 5, 0);
				}
			}
		}
		if (_CraftShow == 13)
		{
			if (INVENTORYMANAGER->findItem("item_12") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_12")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_12")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::DEMONITE_BAR, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_13"), 1, 0);
				}
			}
		}
		if (_CraftShow == 14)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr && INVENTORYMANAGER->findItem("item_3")!=nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::COPPER_PICKAXE, ItemType::PICKAXE, IMAGEMANAGER->findImage("Item_14"), 4.0f, 10.0f,35);
				}
			}
		}
		if (_CraftShow == 15)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr && INVENTORYMANAGER->findItem("item_3")!=nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack()>=3)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::COPPER_AXE, ItemType::AXE, IMAGEMANAGER->findImage("Item_15"),3, 10.0f, 35);
				}
			}
		}
		if (_CraftShow == 16)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr&&INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack()>=3)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::COPPER_HAMMER, ItemType::HAMMER, IMAGEMANAGER->findImage("Item_16"),4, 10.0f, 35);
				}
			}
		}
		if (_CraftShow == 17)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack()>=3)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::COPPER_SWORD, ItemType::SWORD, IMAGEMANAGER->findImage("Item_17"),8, 20.0f);
				}
			}
		}
		if (_CraftShow == 18)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr && INVENTORYMANAGER->findItem("item_3")!=nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::IRON_PICKAXE, ItemType::PICKAXE, IMAGEMANAGER->findImage("Item_18"),5, 10.0f,50);
				}
			}
		}
		if (_CraftShow == 19)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::IRON_AXE, ItemType::AXE, IMAGEMANAGER->findImage("Item_19"),5,10.0f, 50);
				}
			}
		}
		if (_CraftShow == 20)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr && INVENTORYMANAGER->findItem("item_3")!=nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack()>=3)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::IRON_HAMMER, ItemType::HAMMER, IMAGEMANAGER->findImage("Item_20"),7,10.0f,50);
				}
			}
		}

		if (_CraftShow == 21)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr && INVENTORYMANAGER->findItem("item_3")!=nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack()>=3)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::IRON_SWORD, ItemType::SWORD, IMAGEMANAGER->findImage("Item_"),10,20.0f);
				}
			}
		}
		
		if (_CraftShow == 22)
		{
			if (INVENTORYMANAGER->findItem("item_10") != nullptr &&INVENTORYMANAGER->findItem("item_3")!=nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_10")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack()>=3)
				{
					INVENTORYMANAGER->findItem("item_10")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::GOLD_PICKAXE, ItemType::PICKAXE, IMAGEMANAGER->findImage("Item_22"),6,10.0f,55);
				}
			}
		}

		if (_CraftShow == 23)
		{
			if (INVENTORYMANAGER->findItem("item_10") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_10")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_10")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::GOLD_AXE, ItemType::AXE, IMAGEMANAGER->findImage("Item_23"), 7, 10.0f, 55);
				}
			}
		}
		if (_CraftShow == 24)
		{
			if (INVENTORYMANAGER->findItem("item_10") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_10")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_10")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x, _y, type::GOLD_HAMMER, ItemType::HAMMER, IMAGEMANAGER->findImage("Item_24"), 9, 10.0f, 55);
				}
			}
		}

		if (_CraftShow == 26)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x-20, _y-20, type::PLATINUM_PICKAXE, ItemType::PICKAXE, IMAGEMANAGER->findImage("Item_26"), 8, 20,100);
				}
			}
		}
		if (_CraftShow == 27)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::PLATINUM_AXE, ItemType::AXE, IMAGEMANAGER->findImage("Item_27"), 8, 20, 100);
				}
			}
		}
		if (_CraftShow == 28)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::PLATINUM_HAMMER, ItemType::HAMMER, IMAGEMANAGER->findImage("Item_28"), 10, 20, 100);
				}
			}
		}
		if (_CraftShow == 29)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::PLATINUM_SWORD, ItemType::SWORD, IMAGEMANAGER->findImage("Item_29"), 15, 20, 100);
				}
			}
		}
		if (_CraftShow == 30)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONITE_PICKAXE, ItemType::PICKAXE, IMAGEMANAGER->findImage("Item_30"), 9, 20, 150);
				}
			}
		}
		if (_CraftShow == 31)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONITE_AXE, ItemType::AXE, IMAGEMANAGER->findImage("Item_31"),20, 20, 150);
				}
			}
		}
		if (_CraftShow == 32)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONITE_HAMMER, ItemType::HAMMER, IMAGEMANAGER->findImage("Item_32"), 24, 20, 150);
				}
			}
		}
		if (_CraftShow == 33)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 3)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(3);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONITE_SWORD, ItemType::SWORD, IMAGEMANAGER->findImage("Item_33"), 17, 20, 150);
				}
			}
		}
		if (_CraftShow == 34)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::COPPER_HELMET, ItemType::HELMET, IMAGEMANAGER->findImage("Item_34"),1.0f);
				}
			}
		}
		if (_CraftShow == 35)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::COPPER_ARMOR, ItemType::ARMOR, IMAGEMANAGER->findImage("Item_35"),2.0f);
				}
			}
		}
		if (_CraftShow == 36)
		{
			if (INVENTORYMANAGER->findItem("item_8") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_8")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_8")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::COPPER_LEGGINGS, ItemType::LEGGINGS, IMAGEMANAGER->findImage("Item_36"), 1.0f);
				}
			}
		}
		if (_CraftShow == 37)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::IRON_HELMET, ItemType::HELMET, IMAGEMANAGER->findImage("Item_37"), 2.0f);
				}
			}
		}
		if (_CraftShow == 38)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::IRON_ARMOR, ItemType::ARMOR, IMAGEMANAGER->findImage("Item_38"), 3.0f);
				}
			}
		}
		if (_CraftShow == 39)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::IRON_LEGGINGS, ItemType::LEGGINGS, IMAGEMANAGER->findImage("Item_39"), 2.0f);
				}
			}
		}
		if (_CraftShow == 40)
		{
			if (INVENTORYMANAGER->findItem("item_10") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_10")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_10")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::GOLD_HELMET, ItemType::HELMET, IMAGEMANAGER->findImage("Item_40"),4.0f);
				}
			}
		}
		if (_CraftShow == 41)
		{
			if (INVENTORYMANAGER->findItem("item_10") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_10")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_10")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::GOLD_ARMOR, ItemType::ARMOR, IMAGEMANAGER->findImage("Item_41"), 5.0f);
				}
			}
		}
		if (_CraftShow == 42)
		{
			if (INVENTORYMANAGER->findItem("item_10") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_10")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_10")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::GOLD_LEGGINGS, ItemType::LEGGINGS, IMAGEMANAGER->findImage("Item_42"), 4.0f);
				}
			}
		}
		if (_CraftShow == 43)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::PLATINUM_HELMET, ItemType::HELMET, IMAGEMANAGER->findImage("Item_43"), 5.0f);
				}
			}
		}
		if (_CraftShow == 44)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::PLATINUM_ARMOR, ItemType::ARMOR, IMAGEMANAGER->findImage("Item_44"), 6.0f);
				}
			}
		}
		if (_CraftShow == 45)
		{
			if (INVENTORYMANAGER->findItem("item_11") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_11")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_11")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::PLATINUM_LEGGINGS, ItemType::LEGGINGS, IMAGEMANAGER->findImage("Item_45"),5.0f);
				}
			}
		}
		if (_CraftShow == 46)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONITE_HELMET, ItemType::HELMET, IMAGEMANAGER->findImage("Item_46"), 6.0f);
				}
			}
		}
		if (_CraftShow == 47)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONITE_ARMOR, ItemType::ARMOR, IMAGEMANAGER->findImage("Item_47"), 7.0f);
				}
			}
		}
		if (_CraftShow == 48)
		{
			if (INVENTORYMANAGER->findItem("item_13") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_13")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_13")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONITE_LEGGINGS, ItemType::LEGGINGS, IMAGEMANAGER->findImage("Item_48"), 6.0f);
				}
			}
		}
		if (_CraftShow == 53)
		{
			if (INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DESK, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_53"),1);
				}
			}
		}
		if (_CraftShow == 54)
		{
			if (INVENTORYMANAGER->findItem("item_2") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_2")->getItemStack() >= 10)
				{
					INVENTORYMANAGER->findItem("item_2")->removeItemStack(10);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::FURNACE, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_54"), 1);
				}
			}
		}
		if (_CraftShow == 55)
		{
			if (INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 8)
				{
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(8);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::WORKBENCH, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_55"), 1);
				}
			}
		}
		if (_CraftShow == 56)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 8)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(8);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::ANVIL, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_56"), 1);
				}
			}
		}
		if (_CraftShow == 57)
		{
			if (INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 5)
				{
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(5);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::CHIR, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_57"), 1);
				}
			}
		}
		if (_CraftShow == 58)
		{
			if (INVENTORYMANAGER->findItem("item_9") != nullptr && INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_9")->getItemStack() >= 5 && INVENTORYMANAGER->findItem("item_3")->getItemStack()>=8)
				{
					INVENTORYMANAGER->findItem("item_9")->removeItemStack(5);
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(8);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::BOX, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_58"), 1);
				}
			}
		}
		if (_CraftShow == 59)
		{
			if (INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 6)
				{
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(6);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DOOR, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_59"), 1);
				}
			}
		}
		if (_CraftShow == 60)
		{
			if (INVENTORYMANAGER->findItem("item_3") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_3")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_3")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::WOOD_WALL, ItemType::WALL, IMAGEMANAGER->findImage("Item_60"), 4);
				}
			}
		}
		if (_CraftShow == 63)
		{
			if (INVENTORYMANAGER->findItem("item_62") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_62")->getItemStack() >= 6)
				{
					INVENTORYMANAGER->findItem("item_62")->removeItemStack(6);
					ITEMMANAGER->CreateItem(_x - 20, _y - 20, type::DEMONEYE, ItemType::CONSUMBLE, IMAGEMANAGER->findImage("Item_59"), 1);
				}
			}
		}

		if (_CraftShow == 68)
		{
			if (INVENTORYMANAGER->findItem("item_1") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_1")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_1")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x, _y, type::DIRT_WALL, ItemType::WALL, IMAGEMANAGER->findImage("Item_68"), 4);
				}
			}
		}
		if (_CraftShow == 69)
		{
			if (INVENTORYMANAGER->findItem("item_2") != nullptr)
			{
				if (INVENTORYMANAGER->findItem("item_2")->getItemStack() >= 1)
				{
					INVENTORYMANAGER->findItem("item_2")->removeItemStack(1);
					ITEMMANAGER->CreateItem(_x, _y, type::STONE_WALL, ItemType::WALL, IMAGEMANAGER->findImage("Item_68"), 4);
				}
			}
		}
	}
	CraftingList();

}

void Crafting::CraftingList()
{
	for (int i = 0;i < MaxItem;i++)
	{
		if (PtInRect(&_scrollRect[i], _ptMouse))
		{
			_CraftShow = i;
		}
	}
}
