#pragma once
#include"gameNode.h"
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

