#pragma once
#include"gameNode.h"
enum class MeterialItem
{
	WOOD,COPPER,COPPERBAR,IRON,IRONBAR,GOLD,GOLDBAR,PLATINUM,PLATINUMBAR,DEMONITE,LENS,GEL,
};
//�� ������
enum class BlockItem
{
	DIRT,STONE,WOOD,
};
//�� ������
enum class WallItem
{
	DIRT,STONE,WOOD,
};
//�Ҹ�ǰ ������ ex)����
enum class consumbleItem
{
	HEARTCRYSTAL,
};
//�������� ������
enum class WeaponItem
{
	COPPER_SWORD,IRON_SWORD,GOLD_SWORD,PLATINUM_SWORD,DEMONITE_SWORD,
};
//������ ������
enum class ToolsItem
{
	COPPER_PICKAXE, COPPER_AXE, COPPER_HAMMER,
	IRON_PICKAXE, IRON_AXE, IRON_HAMMER,
	GOLD_PICKAXE, GOLD_AXE, GOLD_HAMMER,
	PLATINUM_PICKAXE, PLATINUM_AXE, PLATINUM_HAMMER,
	DEMONITE_PICKAXE, DEMONITE_AXE, DEMONITE_HAMMER,
};
struct MeterialItemInfo
{
	MeterialItem itemType;
	int itemStack;
};
struct BlockItemInfo
{
	BlockItem itemType;
	int itemStack;
};
struct WallItemInfo
{
	WallItem itemType;
	int itemStack;
};
struct ConsumbleItemtInfo
{
	consumbleItem itemType;
	int itemStack;
};
struct WeaponItemInfo
{
	WeaponItem itemType;
	int itemStack;
};
struct ToolsItemInfo
{
	ToolsItem itemType;
	int ItemStack;
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

