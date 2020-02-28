#pragma once
#include"gameNode.h"
#include"Item.h"
#include"Tile.h"
#include<vector>

#define MaxBlockTile_X 8
#define MaxBlockTile_Y 19

struct tagSetTile
{
	RECT rc;
	int FrameX;
	int FrameY;
	float burglar;
	TileType SetTileType;
	BlockType SetBlockType;
	WallType SetWallType;
	ObjectType SetObjectType;
};
struct SelectTile
{
	int FrameX, FrameY;
	float burglar;
	TileType SelectTileType;
	BlockType SelectBlockType;
	WallType SelectWallType;
	ObjectType SelectObjectType;
	bool Select;
};
class MapTool :public gameNode
{
private:
	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viTile;
private:
	POINT _winsize;
	POINT _CameraPositon;
	tagTile _Tile[MaxTile_X][MaxTile_Y];
	
	RECT _TileUI;
	tagSetTile _UITile[MaxBlockTile_X][MaxBlockTile_Y];
	SelectTile _selectTile;
	RECT _button[12];
	POINT _start;
public:

	MapTool() {};
	~MapTool() {};
	
	HRESULT init();
	void release();
	void update();
	void render();

	void draw();
	void blockTileInit();
	void ButtonInit();
	void ButtonControl();
	void CameraControl();				//카메라를 조종할 함수
	void changeTileList();				//타일 목록을 바꿔줄 함수
	void selectTile();					//클릭시 현재 선택한 타일을 바꾸어줄 함수
	void blockFrameSet(int x,int y);
	void wallFrameSet(int x, int y);
	void objectFrameSet(int x, int y);
	void treeFrameSet(int x, int y);
	void drawTile();					//화면에 나오는 타일을 현재 선택한 타일로 바꾸어주는 함수

	void Save();
	void Load();
};

