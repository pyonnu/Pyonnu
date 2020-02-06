#pragma once
#include"gameNode.h"
#include<map>
#include<vector>
enum class TileType
{
	PLAYER,ENEMY,WALL,BLOCK
};
enum class BlockType
{
//   벽   일반   문    플래폼  상자
	WALL,NORMAL,DOOR,PLATFORM,BOX,
};
struct tagTile
{
	int idx, idy;			//index번호
	int x, y;				//실질적인 x,y좌표
	RECT rc;				//타일의 몸뚱아리
	TileType tileType;		//타일의 종류
	BlockType blockType;	//블록의 중류
};
class MapTool :public gameNode
{
private:
	POINT _winsize;
	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viTile;
public:

	MapTool() {};
	~MapTool() {};

	HRESULT init();
	void release();
	void update();
	void render();
	
};

