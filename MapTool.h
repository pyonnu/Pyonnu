#pragma once
#include"gameNode.h"
#include"Item.h"
#include<vector>

#define TILESIZE 32			//타일 한개 사이즈
//총 720,000타일
#define MaxTile_X 400	//최대 x크기
#define MaxTile_Y 250	//최대 y크기

enum class TileType
{
	PLAYER,ENEMY,WALL,BLOCK,OBJECT
};

struct tagTile
{
	int idx, idy;			//index번호
	int x, y;				//실질적인 x,y좌표
	RECT rc;				//타일의 몸뚱아리
	TileType tileType;		//타일의 종류
	BlockType blockType;	//블럭의 종류
	WallType wallType;		//벽의 종류
};
class MapTool :public gameNode
{
private:
	POINT _winsize;
	POINT _CameraPositon;
	tagTile _Tile[MaxTile_X][MaxTile_Y];
	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viTile;
	RECT _TileUI;
	RECT _button[12];
public:

	MapTool() {};
	~MapTool() {};

	HRESULT init();
	void release();
	void update();
	void render();
	
};

