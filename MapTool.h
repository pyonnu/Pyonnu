#pragma once
#include"gameNode.h"
#include"Item.h"
#include<vector>

#define TILESIZE 32			//Ÿ�� �Ѱ� ������
//�� 80,000Ÿ��
#define MaxTile_X 400	//�ִ� xũ��
#define MaxTile_Y 200	//�ִ� yũ��

#define MaxBlockTile_X 8
#define MaxBlockTile_Y 14
enum class TileType
{
	PLAYER,ENEMY,WALL,BLOCK,OBJECT
};
enum class ObjectType
{
	TREE, DEMONATLER, HEARTCRYSTAL, OPENDOOR, CHIR, FURNACE, BOX, 
};
enum class PlatFormType
{
	WOODPLATFORM,DESK,WORKBENCH,ANVIL,
};
struct tagTile
{
	int idx, idy;			//index��ȣ
	int x, y;				//�������� x,y��ǥ
	RECT rc;				//Ÿ���� ���׾Ƹ�
	BlockType blockType;	//���� ����
	WallType wallType;		//���� ����
	ObjectType objectType;
	PlatFormType platFormType;
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
	PlatFormType SetPlatFormType;
};
struct SelectTile
{
	int FrameX, FrameY;
	TileType SelectTileType;
	BlockType SelectBlockType;
	WallType SelectWallType;
	ObjectType SelectObjectType;
	PlatFormType SelectPlatFormType;
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
	tagSetTile _blockTile[MaxBlockTile_X][MaxBlockTile_Y];
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

	void ButtonInit();

	void CameraControl();				//ī�޶� ������ �Լ�
	void changeTileList();				//Ÿ�� ����� �ٲ��� �Լ�
	void selectTile();					//Ŭ���� ���� ������ Ÿ���� �ٲپ��� �Լ�
	void drawTile();					//ȭ�鿡 ������ Ÿ���� ���� ������ Ÿ�Ϸ� �ٲپ��ִ� �Լ�

	void Save();
	void Load();
};

