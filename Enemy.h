#pragma once
#include"gameNode.h"
class Enemy:public gameNode
{
protected:

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

