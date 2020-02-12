#pragma once
#include"gameNode.h"
#include"Item.h"
#include<vector>

#define TILESIZE 32			//타일 한개 사이즈
//총 8,400타일
#define MaxTile_X 120	//최대 x크기
#define MaxTile_Y 70	//최대 y크기

#define MaxBlockTile_X 8
#define MaxBlockTile_Y 10
enum class TileType
{
	PLAYER,ENEMY,WALL,BLOCK,OBJECT,TREE
};
//화면에 보일 타일종류
struct tagTile
{
	int idx, idy;			//index번호
	int x, y;				//실질적인 x,y좌표
	int FrameX, FrameY;
	int FrameX2, FrameY2;
	RECT rc;				//타일의 몸뚱아리
	TileType tileType;		//타일의 종류
	BlockType blockType;	//블럭의 종류
	WallType wallType;		//벽의 종류
	ObjectType objectType;	//오브젝트의 종류
};

struct tagSetTile
{
	RECT rc;
	int FrameX;
	int FrameY;
	TileType SetTileType;
	BlockType SetBlockType;
	WallType SetWallType;
	ObjectType SetObjectType;
};
struct SelectTile
{
	int FrameX, FrameY;
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

