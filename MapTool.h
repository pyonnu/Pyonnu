#pragma once
#include"gameNode.h"
#include"Item.h"
#include<vector>

#define TILESIZE 32			//Ÿ�� �Ѱ� ������
//�� 80,000Ÿ��
#define MaxTile_X 400	//�ִ� xũ��
#define MaxTile_Y 200	//�ִ� yũ��

#define MaxBlockTile_X 8
#define MaxBlockTile_Y 13
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
struct tagSetTile
{
	RECT rc;
	int FrameX;
	int FrameY;
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
	tagSetTile _blockTile[MaxBlockTile_X][MaxBlockTile_Y];
	RECT _button[12];
public:

	MapTool() {};
	~MapTool() {};
	
	HRESULT init();
	void release();
	void update();
	void render();
	
	void Save();
	void Load();
};

