#pragma once
#include"gameNode.h"
#include"Item.h"
#include<vector>

#define TILESIZE 32			//Ÿ�� �Ѱ� ������
//�� 8,400Ÿ��
#define MaxTile_X 120	//�ִ� xũ��
#define MaxTile_Y 70	//�ִ� yũ��

#define MaxBlockTile_X 8
#define MaxBlockTile_Y 10
enum class TileType
{
	PLAYER,ENEMY,WALL,BLOCK,OBJECT,TREE
};
//ȭ�鿡 ���� Ÿ������
struct tagTile
{
	int idx, idy;			//index��ȣ
	int x, y;				//�������� x,y��ǥ
	int FrameX, FrameY;
	int FrameX2, FrameY2;
	RECT rc;				//Ÿ���� ���׾Ƹ�
	TileType tileType;		//Ÿ���� ����
	BlockType blockType;	//���� ����
	WallType wallType;		//���� ����
	ObjectType objectType;	//������Ʈ�� ����
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
	
	void CameraControl();				//ī�޶� ������ �Լ�
	void changeTileList();				//Ÿ�� ����� �ٲ��� �Լ�
	void selectTile();					//Ŭ���� ���� ������ Ÿ���� �ٲپ��� �Լ�
	void blockFrameSet(int x,int y);
	void wallFrameSet(int x, int y);
	void objectFrameSet(int x, int y);
	void treeFrameSet(int x, int y);
	void drawTile();					//ȭ�鿡 ������ Ÿ���� ���� ������ Ÿ�Ϸ� �ٲپ��ִ� �Լ�

	void Save();
	void Load();
};

