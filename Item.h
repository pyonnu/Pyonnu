#pragma once
#include"gameNode.h"

enum class BlockType
{
	NONE, DIRT, WOOD, STONE, COPPER, IRON, GOLD, PLATINUM, PLATFORM, DOOR, BOX,CHIR,DESK,WORKBENCH,ANVIL,
};
enum class WallType
{
	NONE, DIRT, WOOD, STONE,
};
enum class MeterialType
{
	WOOD,COPPER,COPPERBAR,IRON,IRONBAR,GOLD,GOLDBAR,PLATINUM,PLATINUMBAR,DEMONITE,LENS,GEL
};
//소모품 아이템 ex)물약
enum class consumbleItem
{

};
//공격전용 아이템
enum class WeaponItem
{
	SWORD, SPEAR,
};
//도구용 아이템
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

