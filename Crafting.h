#pragma once

#define MaxItem 70
class Crafting
{
private:
	RECT _craftRect1[20];
	RECT _craftRect2[20];
	RECT _craftRect3[20];
	RECT _craftRect4[20];
	RECT _scrollRect[MaxItem];
	RECT _showRecipe;
	RECT _showCraft;
	RECT _CraftUIPos[4];
	RECT _UpDownButton[2];
	image* _showCraftImage[MaxItem];
	int _CraftShow;
	int _craftNum;
	int _craftPage;
	bool _showRecipeList;
	bool _invenSee;
	float _x, _y;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC dc);
	void draw(HDC dc);

	void setXY(float x, float y) { _x = x;_y = y; }
	void CraftingControl();
	void ButtonClick();
	void CraftingList();
	void setInvensee(bool TF) { _invenSee = TF; }
};