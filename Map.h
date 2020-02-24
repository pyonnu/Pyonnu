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
	int _startX, _startY, _endX, _endY;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void render(float x, float y);

	void setMap();
	void objectTileUpdate(int x,int y);
	vector<tagTile*> getVTile() { return _vTile; }
	vector<tagTile*>::iterator getViTile() { return _viTile; }
	void setXY(int x1, int x2, int y1, int y2) { _startX = x1;_endX = x2;_startY = y1;_endY = y2; }
};

