#pragma once
#include"gameNode.h"

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
	NONE,DEMONATLER, HEARTCRYSTAL, OPENDOOR, CLOSEDOOR, FURNACE, BOX, WORKBENCH,CHIR,DESK,ANVIL,TREE
};
enum class MeterialType
{
	WOOD,COPPER,COPPERBAR,IRON,IRONBAR,GOLD,GOLDBAR,PLATINUM,PLATINUMBAR,DEMONITE,LENS,GEL
};
//�Ҹ�ǰ ������ ex)����
enum class consumbleItem
{

};
//�������� ������
enum class WeaponItem
{
	SWORD, SPEAR,
};
//������ ������
enum class ToolsItem
{
	PICKAXE, AXE, HAMMER
};
class Item :public gameNode
{
private:
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

