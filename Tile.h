#pragma once

#define TILESIZE 32			//타일 한개 사이즈

//총 21,600타일
#define MaxTile_X 240	//최대 x크기
#define MaxTile_Y 90	//최대 y크기
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
	//int idx, idy;			//index번호
	int x, y;				//실질적인 x,y좌표
	int FrameX, FrameY;
	int FrameX2, FrameY2;
	int FrameX3, FrameY3;
	RECT rc;				//타일의 몸뚱아리
	TileType tileType;		//타일의 종류
	BlockType blockType;	//블럭의 종류
	WallType wallType;		//벽의 종류
	ObjectType objectType;	//오브젝트의 종류

	// 만약에 struct 나 class에서 비교 연산이 필요할때 선언해야한다.
	//bool operator=( tagTile &other ) {
	//	bool a;
	//	a& index.x == other.index.x;
	//	a& index.y == other.index.y;
	//	a& x == other.x;
	//	a& y == other.y;
	//}
};

