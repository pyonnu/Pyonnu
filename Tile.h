#pragma once

#define TILESIZE 32			//Ÿ�� �Ѱ� ������

//�� 21,600Ÿ��
#define MaxTile_X 240	//�ִ� xũ��
#define MaxTile_Y 90	//�ִ� yũ��
enum class TileType
{
	PLAYER, ENEMY, WALL, BLOCK, OBJECT, NONE
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
	NONE, DESK1, DESK2, DESK3, DESK4, DESK5,DESK6, HEARTCRYSTAL1, HEARTCRYSTAL2, HEARTCRYSTAL3, HEARTCRYSTAL4,
	LEFTCHIR1, LEFTCHIR2, RIGHTCHIR1, RIGHTCHIR2, FURNACE1, FURNACE2, FURNACE3, FURNACE4, FURNACE5, FURNACE6,
	BOX1, BOX2, BOX3, BOX4, WORKBENCH1, WORKBENCH2, ANVIL1, ANVIL2,
	RIGHT_OPENDOOR1, RIGHT_OPENDOOR2, RIGHT_OPENDOOR3, RIGHT_OPENDOOR4, RIGHT_OPENDOOR5, RIGHT_OPENDOOR6,
	LEFT_OPENDOOR1, LEFT_OPENDOOR2, LEFT_OPENDOOR3, LEFT_OPENDOOR4, LEFT_OPENDOOR5, LEFT_OPENDOOR6,
	CLOSEDOOR1, CLOSEDOOR2, CLOSEDOOR3, DEMONALTER1, DEMONALTER2, DEMONALTER3, DEMONALTER4, DEMONALTER5, DEMONALTER6,
	TREE1, TREE2, TREE3, TREE4, TREE5, TREE6, TREE7, TREE8, TREE9, TREE10, TREE11, TREE12, TREE13, TREE14, TREE15,
	TREE16, TREE17, TREE18, TREE19, TREE20, TREE21, TREE22, TREE23, TREE24, TREE25, TREE26, TREE27,
	TREE28, TREE29, TREE30, TREE31, TREE32, TREE33, TREE34, TREE35, TREE36, TREE37, TREE38,
	TREE39, TREE40, TREE41, TREE42, TREE43, TREE44, TREE45, TREE46, TREE47, TREE48, TREE49, TREE50,
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