#pragma once
#include"gameNode.h"
#include"Tile.h"
#include<vector>
class Map :public gameNode
{
private:
	tagTile _Tile[MaxTile_X][MaxTile_Y];
	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viTile;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setMap();
};

