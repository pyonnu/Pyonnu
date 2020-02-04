#pragma once
#include"gameNode.h"
class MapTool :public gameNode
{
private:

public:

	MapTool() {};
	~MapTool() {};

	HRESULT init();
	void release();
	void update();
	void render();
};

