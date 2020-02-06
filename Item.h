#pragma once
#include"gameNode.h"

enum class BlockItem
{
	DIRT, WOOD, STONE, COPPER, IRON, SILVER, GOLD, PLATFORM, DOOR, BOX,
};
enum class WallItem
{
	TERRA, WOOD, STONE,
};
enum class MeterialItem
{

};
enum class consumbleItem
{

};
enum class WeaponItem
{

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

