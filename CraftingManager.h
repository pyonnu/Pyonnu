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
};

