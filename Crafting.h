#pragma once
#include"gameNode.h"
class Crafting :public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

