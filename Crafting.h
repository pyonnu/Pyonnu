#pragma once
#include"gameNode.h"
#include"Item.h"
class Crafting :public gameNode
{
private:
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

