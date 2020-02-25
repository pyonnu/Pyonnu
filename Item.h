#pragma once

enum class MeterialItem
{
	WOOD, COPPER, COPPERBAR, IRON, IRONBAR, GOLD, GOLDBAR, PLATINUM, PLATINUMBAR, DEMONITE, LENS, GEL,
};
//블럭 아이템
enum class BlockItem
{
	DIRT, STONE, WOOD,
};
//벽 아이템
enum class WallItem
{
	DIRT, STONE, WOOD,
};
//소모품 아이템 ex)물약
enum class consumbleItem
{
	HEARTCRYSTAL,
};
//공격전용 아이템
enum class WeaponItem
{
	COPPER_SWORD, IRON_SWORD, GOLD_SWORD, PLATINUM_SWORD, DEMONITE_SWORD,
};
//도구용 아이템
enum class ToolsItem
{
	COPPER_PICKAXE, COPPER_AXE, COPPER_HAMMER,
	IRON_PICKAXE, IRON_AXE, IRON_HAMMER,
	GOLD_PICKAXE, GOLD_AXE, GOLD_HAMMER,
	PLATINUM_PICKAXE, PLATINUM_AXE, PLATINUM_HAMMER,
	DEMONITE_PICKAXE, DEMONITE_AXE, DEMONITE_HAMMER,
};
enum class type
{
	NONE, DIRT_BLOCK, STONE_BLOCK, WOOD, COPPER, COPPER_BAR, IRON, IRON_BAR, GOLD, GOLD_BAR, PLATINUM, PLATINUM_BAR, DEMONITE, DEMONITE_BAR,
	COPPER_PICKAXE, COPPER_AXE, COPPER_HAMMER, COPPER_SWORD, IRON_PICKAXE, IRON_AXE, IRON_HAMMER, IRON_SWORD, GOLD_PICKAXE, GOLD_AXE, GOLD_HAMMER, GOLD_SWORD,
	PLATINUM_PICKAXE, PLATINUM_AXE, PLATINUM_HAMMER, PLATINUM_SWORD, DEMONITE_PICKAXE, DEMONITE_AXE, DEMONITE_HAMMER, DEMONITE_SWORD,
	COPPER_HELMET, COPPER_ARMOR, COPPER_LEGGINGS, IRON_HELMET, IRON_ARMOR, IRON_LEGGINGS, GOLD_HELMET, GOLD_ARMOR, GOLD_LEGGINGS, PLATINUM_HELMET, PLATINUM_ARMOR, PLATINUM_LEGGINGS,
	DEMONITE_HELMET, DEMONITE_ARMOR, DEMONITE_LEGGINGS, COPPER_COIN, IRON_COIN, GOLD_COIN, PLATINUM_COIN,
	DESK, FURNACE, WORKBENCH, ANVIL, CHIR, BOX, DOOR, WOOD_WALL, GEL, LENS,
	DEMONEYE, POTION50, POTION100, ACORN, HEARTCRYSTAL,
};
enum class ItemType
{
	NONE, BLOCK, WALL, METERIAL, CONSUMBLE, PICKAXE, AXE, HAMMER, SWORD, HELMET, ARMOR, LEGGINGS, COIN,
};

class Item
{
public:

	typedef struct tagItemInfo
	{
		type Type;
		ItemType itemType;
		ItemType itemType2;
		image* itemImage;
		int itemStack;
		float weaponDamage;
		float ArmorDefense;
		float PotionHealthPoint;
		RECT rc;
		tagItemInfo()
		{
			Type = type::NONE;
			itemType = ItemType::NONE;
			itemType2 = ItemType::NONE;
			itemImage = NULL;
			itemStack = NULL;
			weaponDamage = NULL;
			ArmorDefense = NULL;
			PotionHealthPoint = NULL;
		}
	}Item_Info, * PItem_Info;

private:
	PItem_Info _itemInfo;
public:
	HRESULT init(type type, ItemType type2, string image, int stack);
	HRESULT init(type type, ItemType type2, ItemType type3, string image, int stack);
	HRESULT init(type type, ItemType type2, string image, int stack, float point);

	HRESULT init(type type, ItemType type2, image* image, int stack);
	HRESULT init(type type, ItemType type2, ItemType type3, image* image, int stack);
	HRESULT init(type type, ItemType type2, image* image, int stack, float point);

	void release();
	void update();
	void render(HDC dc);
	void render(HDC dc, float x, float y);

	void CreateItem(float x, float y);
	
	inline type getItemType() { return _itemInfo->Type; }
	inline ItemType getItemType1() { return _itemInfo->itemType; }
	inline ItemType getItemType2() { return _itemInfo->itemType2; }
	inline int getItemStack() { return _itemInfo->itemStack; }
	inline float getWeaponDamage() { return _itemInfo->weaponDamage; }
	inline float getArmorDefense() { return _itemInfo->ArmorDefense; }
	inline float getPotionPower() { return _itemInfo->PotionHealthPoint; }
	inline RECT getRect() { return _itemInfo->rc; }

	inline void setItemStack(int stack) { _itemInfo->itemStack = stack; }
	inline void PlusItemStack() { _itemInfo->itemStack += 1; }
	inline void setWeaponDamage(float damage) { _itemInfo->weaponDamage = damage; }
	inline void setArmorDefense(float defense) { _itemInfo->ArmorDefense = defense; }
};

