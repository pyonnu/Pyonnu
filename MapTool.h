#pragma once
#include"gameNode.h"
#include"Item.h"
#include<vector>

#define TILESIZE 32			//Ÿ�� �Ѱ� ������
//�� 720,000Ÿ��
#define MaxTile_X 400	//�ִ� xũ��
#define MaxTile_Y 250	//�ִ� yũ��

enum class TileType
{
	PLAYER,ENEMY,WALL,BLOCK,OBJECT
};

struct tagTile
{
	int idx, idy;			//index��ȣ
	int x, y;				//�������� x,y��ǥ
	RECT rc;				//Ÿ���� ���׾Ƹ�
	TileType tileType;		//Ÿ���� ����
	BlockType blockType;	//���� ����
	WallType wallType;		//���� ����
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

