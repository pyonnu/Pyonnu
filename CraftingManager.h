#pragma once
#include"Crafting.h"
#include"singletonBase.h"
class CraftingManager:public singletonBase<CraftingManager>
{
private:
	Crafting* _crafting;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC dc);

	void ButtonClick();
	void InvenSee(bool TF) { _crafting->setInvensee(TF); }
	void setworkbench(bool workbench, bool anvil, bool furnace, bool demonalter) { _crafting->setworkbench(workbench, anvil, furnace, demonalter);}
	void setXY(float x, float y);
};

