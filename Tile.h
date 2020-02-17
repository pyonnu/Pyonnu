#pragma once

#define TILESIZE 32			//Ÿ�� �Ѱ� ������

//�� 21,600Ÿ��
#define MaxTile_X 240	//�ִ� xũ��
#define MaxTile_Y 90	//�ִ� yũ��
enum class TileType
{
	PLAYER, ENEMY, WALL, BLOCK, OBJECT,
};
enum class BlockType
{
	NONE, DIRT, WOOD, STONE, COPPER, IRON, GOLD, PLATINUM,
};
enum class WallType
{
	NONE, DIRT, WOOD, STONE,
};
enum class ObjectType
{
	NONE, DEMONATLER, HEARTCRYSTAL, LEFTOPENDOOR,RIGHTOPENDOOR, CLOSEDOOR, FURNACE, BOX, WORKBENCH, CHIR, DESK, ANVIL, TREE
};

struct tagTile
{
	POINT index;
	//int idx, idy;			//index��ȣ
	int x, y;				//�������� x,y��ǥ
	int FrameX, FrameY;
	int FrameX2, FrameY2;
	int FrameX3, FrameY3;
	RECT rc;				//Ÿ���� ���׾Ƹ�
	TileType tileType;		//Ÿ���� ����
	BlockType blockType;	//���� ����
	WallType wallType;		//���� ����
	ObjectType objectType;	//������Ʈ�� ����

	// ���࿡ struct �� class���� �� ������ �ʿ��Ҷ� �����ؾ��Ѵ�.
	//bool operator=( tagTile &other ) {
	//	bool a;
	//	a& index.x == other.index.x;
	//	a& index.y == other.index.y;
	//	a& x == other.x;
	//	a& y == other.y;
	//}
};

