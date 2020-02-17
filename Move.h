#pragma once
#include"gameNode.h"
class Move:public gameNode
{
private:
	float* _x;
	float* _y;

public:
	HRESULT init();
	void release();
	void update();

};

