#pragma once
#include"gameNode.h"

enum class BlockType
{
	NONE, TERRA, WOOD, STONE, COPPER, IRON, SILVER, GOLD, PLATFORM, DOOR, BOX,
};
enum class WallType
{
	NONE, TERRA, WOOD, STONE,
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

