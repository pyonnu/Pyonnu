#pragma once
#include"gameNode.h"
enum class MeterialItem
{
	WOOD,COPPER,COPPERBAR,IRON,IRONBAR,GOLD,GOLDBAR,PLATINUM,PLATINUMBAR,DEMONITE,LENS,GEL
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
	HEARTCRYSTAL
};
//�������� ������
enum class WeaponItem
{
	SWORD, SPEAR,
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
class Item :public gameNode
{
private:
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

