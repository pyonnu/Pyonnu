#pragma once
#include"gameNode.h"
#include"Tile.h"
#include<vector>
#include<map>
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
	void render(float x, float y);
	void setMap();

	vector<tagTile*> getVTile() { return _vTile; }
	vector<tagTile*>::iterator getViTile() { return _viTile; }
};

