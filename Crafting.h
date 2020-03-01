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
	RECT _UpDownButton[2];
	image* _showCraftImage[MaxItem];
	int _craftNum;
	int _craftPage;
	bool _showRecipeList;
	bool _invenSee;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC dc);
	void draw(HDC dc);

	
	void CraftingControl();
	void ButtonClick();
	void CraftingList();
	void setInvensee(bool TF) { _invenSee = TF; }
};