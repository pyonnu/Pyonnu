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
	_showRecipe = RectMake(82, 392 + 62 * 4, 30, 30);
	_craftNum = 1;
	_showRecipeList = false;
	_invenSee = false;
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
		Rectangle(dc, _UpDownButton[0]);
		Rectangle(dc, _UpDownButton[1]);
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
			Rectangle(dc, _scrollRect[i]);
			_showCraftImage[i]->render(dc, _scrollRect[i].left, _scrollRect[i].top);
		}

	}
	Rectangle(dc, _showRecipe);
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
	cout << _craftNum << endl;
}

void Crafting::ButtonClick()
{
	if (PtInRect(&_showRecipe, _ptMouse))
	{
		if (_showRecipeList)_showRecipeList = false;
		else _showRecipeList = true;
		cout << "push" << endl;
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

	CraftingList();

}

void Crafting::CraftingList()
{
	if (PtInRect(&_scrollRect[1], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[2], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[3], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[4], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[5], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[6], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[7], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[8], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[9], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[10], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[11], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[12], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[13], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[14], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[15], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[16], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[17], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[18], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[19], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[20], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[21], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[22], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[23], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[24], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[25], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[26], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[27], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[28], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[29], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[30], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[31], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[32], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[33], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[34], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[35], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[36], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[37], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[38], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[39], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[40], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[41], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[42], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[43], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[44], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[45], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[46], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[47], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[48], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[49], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[50], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[51], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[52], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[53], _ptMouse))
	{

	}if (PtInRect(&_scrollRect[54], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[55], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[56], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[57], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[58], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[59], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[60], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[61], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[62], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[63], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[64], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[65], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[66], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[67], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[68], _ptMouse))
	{

	}
	if (PtInRect(&_scrollRect[69], _ptMouse))
	{

	}

}
