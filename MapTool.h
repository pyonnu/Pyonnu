#pragma once
#include"gameNode.h"
#include<vector>

#define tileSize 16			//Ÿ�� �Ѱ� ������
//�� 720,000Ÿ��
#define MaxTile_X 1600		//�ִ� xũ��
#define MaxTile_Y 450		//�ִ� yũ��

enum class TileType
{
	PLAYER,ENEMY,WALL,BLOCK
};
enum class BlockType
{
//   ��   �Ϲ�   ��    �÷���  ����
	WALL,NORMAL,DOOR,PLATFORM,BOX,
};
struct tagTile
{
	int idx, idy;			//index��ȣ
	int x, y;				//�������� x,y��ǥ
	RECT rc;				//Ÿ���� ���׾Ƹ�
	TileType tileType;		//Ÿ���� ����
	BlockType blockType;	//����� �߷�
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

