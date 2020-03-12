#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
HRESULT playGround::init()
{
	gameNode::init(true);
	SCENEMANAGER->init();

	imageAdd();
	//itemAdd();
	_scene = new Scene;
	_scene->init();
	return S_OK;
}

//메모리 해제는 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::release()
{
	gameNode::release();

}

//연산은 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	ITEMMANAGER->update();
}

//여기다 그려라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());

	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imageAdd()
{
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■로 비 이 미 지■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->addImage("LobbyImage", "Resources/Lobby/Lobby.bmp", 1280, 720, false, RGB(255, 0, 255));
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	//타 일 이 미 지
	IMAGEMANAGER->addFrameImage("BlockTiles", "Resources/Tiles/BlockTiles.bmp", 256, 32, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WallTiles", "Resources/Tiles/WallTiles.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ObjectTiles", "Resources/Tiles/ObjectTiles.bmp", 224, 544, 7, 17, true, RGB(255, 0, 255));
	//백그라운드 이미지
	IMAGEMANAGER->addImage("Background_1", "Resources/BackGrounds/Background_1.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_2", "Resources/BackGrounds/Background_2.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_3", "Resources/BackGrounds/Background_3.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_4", "Resources/BackGrounds/Background_4.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_5", "Resources/BackGrounds/Backgorund_5.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_6", "Resources/BackGrounds/Backgorund_6.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_7", "Resources/BackGrounds/Backgorund_7.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_8", "Resources/BackGrounds/Backgorund_8.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_9", "Resources/BackGrounds/Backgorund_9.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_10", "Resources/BackGrounds/Backgorund_10.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Background1", "Resources/BackGrounds/Background1.bmp", 7680, 2880, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Background2", "Resources/BackGrounds/Background2.bmp", 7680, 2880, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Background3", "Resources/BackGrounds/Background3.bmp", 7680, 2880, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Background4", "Resources/BackGrounds/Background4.bmp", 7680, 2880, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background5", "Resources/BackGrounds/Background5.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background6", "Resources/BackGrounds/Background6.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background7", "Resources/BackGrounds/Background7.bmp", 1600, 900, true, RGB(255, 0, 255));
	//에너미 이미지
	IMAGEMANAGER->addFrameImage("Slime", "Resources/Enemy/Slime.bmp", 64, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Zombie", "Resources/Enemy/Zombie.bmp", 136, 276, 2, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DemonEye", "Resources/Enemy/DemonEye.bmp", 72,142, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Demon", "Resources/Enemy/Demon.bmp", 328, 272, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss", "Resources/Enemy/EyeOfCthulhu.bmp", 220, 1992, 1, 6, true, RGB(255, 0, 255));
	//플레이어 이미지
	IMAGEMANAGER->addFrameImage("Player_Head", "Resources/Player/Player_Head.bmp", 80 * 2, 2 * 1120, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Player_Body", "Resources/Player/Player_Body.bmp", 80 * 2, 2 * 1120, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Player_Legs", "Resources/Player/Player_Legs.bmp", 80 * 2, 2 * 1120, 2, 20, true, RGB(255, 0, 255));
	//갑옷 이미지
	IMAGEMANAGER->addFrameImage("Armor_Head_1", "Resources/Armor/Head/Armor_Head_1.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Head_2", "Resources/Armor/Head/Armor_Head_2.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Head_3", "Resources/Armor/Head/Armor_Head_3.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Head_4", "Resources/Armor/Head/Armor_Head_4.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Head_5", "Resources/Armor/Head/Armor_Head_5.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Armor_Body_1", "Resources/Armor/Body/Armor_Body_1.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Body_2", "Resources/Armor/Body/Armor_Body_2.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Body_3", "Resources/Armor/Body/Armor_Body_3.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Body_4", "Resources/Armor/Body/Armor_Body_4.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Body_5", "Resources/Armor/Body/Armor_Body_5.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Armor_Legs_1", "Resources/Armor/Legs/Armor_Legs_1.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Legs_2", "Resources/Armor/Legs/Armor_Legs_2.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Legs_3", "Resources/Armor/Legs/Armor_Legs_3.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Legs_4", "Resources/Armor/Legs/Armor_Legs_4.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Armor_Legs_5", "Resources/Armor/Legs/Armor_Legs_5.bmp", 160, 2240, 2, 20, true, RGB(255, 0, 255));

	//UI이미지
	IMAGEMANAGER->addImage("Inventory_Back", "Resources/UI/Inventory_Back.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Inventory_Back14", "Resources/UI/Inventory_Back14.bmp", 62, 62, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Heart", "Resources/UI/Heart.bmp", 44, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ButtonDelete", "Resources/UI/ButtonDelete.bmp", 44, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_0", "Resources/UI/Craft_Toggle_0.bmp", 30,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_1", "Resources/UI/Craft_Toggle_1.bmp", 30,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_2", "Resources/UI/Craft_Toggle_2.bmp", 30,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_3", "Resources/UI/Craft_Toggle_3.bmp", 30,30, true, RGB(255, 0, 255));
	//Item이미지
	IMAGEMANAGER->addImage("Item_0", "Resources/Item/Item_0.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_1", "Resources/Item/Item_1.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_2", "Resources/Item/Item_2.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_3", "Resources/Item/Item_3.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_4", "Resources/Item/Item_4.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_5", "Resources/Item/Item_5.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_6", "Resources/Item/Item_6.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_7", "Resources/Item/Item_7.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_8", "Resources/Item/Item_8.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_9", "Resources/Item/Item_9.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_10", "Resources/Item/Item_10.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_11", "Resources/Item/Item_11.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_12", "Resources/Item/Item_12.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_13", "Resources/Item/Item_13.bmp", 52, 52, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_14", "Resources/Item/Item_14.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_15", "Resources/Item/Item_15.bmp", 86,76, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_16", "Resources/Item/Item_16.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_17", "Resources/Item/Item_17.bmp", 86,86, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_18", "Resources/Item/Item_18.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_19", "Resources/Item/Item_19.bmp", 86,76, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_20", "Resources/Item/Item_20.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_21", "Resources/Item/Item_21.bmp", 86,86, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_22", "Resources/Item/Item_22.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_23", "Resources/Item/Item_23.bmp", 86,76, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_24", "Resources/Item/Item_24.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_25", "Resources/Item/Item_25.bmp", 86,86, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_26", "Resources/Item/Item_26.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_27", "Resources/Item/Item_27.bmp", 86,76, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_28", "Resources/Item/Item_28.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_29", "Resources/Item/Item_29.bmp", 86,86, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_30", "Resources/Item/Item_30.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_31", "Resources/Item/Item_31.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_32", "Resources/Item/Item_32.bmp", 86,86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_33", "Resources/Item/Item_33.bmp", 94, 94, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_34", "Resources/Item/Item_34.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_35", "Resources/Item/Item_35.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_36", "Resources/Item/Item_36.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_37", "Resources/Item/Item_37.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_38", "Resources/Item/Item_38.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_39", "Resources/Item/Item_39.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_40", "Resources/Item/Item_40.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_41", "Resources/Item/Item_41.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_42", "Resources/Item/Item_42.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_43", "Resources/Item/Item_43.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_44", "Resources/Item/Item_44.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_45", "Resources/Item/Item_45.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_46", "Resources/Item/Item_46.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_47", "Resources/Item/Item_47.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_48", "Resources/Item/Item_48.bmp", 52, 52, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_49", "Resources/Item/Item_49.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_50", "Resources/Item/Item_50.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_51", "Resources/Item/Item_51.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_52", "Resources/Item/Item_52.bmp", 52, 52, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_53", "Resources/Item/Item_53.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_54", "Resources/Item/Item_54.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_55", "Resources/Item/Item_55.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_56", "Resources/Item/Item_56.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_57", "Resources/Item/Item_57.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_58", "Resources/Item/Item_58.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_59", "Resources/Item/Item_59.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_60", "Resources/Item/Item_60.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_61", "Resources/Item/Item_61.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_62", "Resources/Item/Item_62.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_63", "Resources/Item/Item_63.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_64", "Resources/Item/Item_64.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_65", "Resources/Item/Item_65.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_66", "Resources/Item/Item_66.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_67", "Resources/Item/Item_67.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_68", "Resources/Item/Item_68.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_69", "Resources/Item/Item_69.bmp", 52, 52, true, RGB(255, 0, 255));
}

void playGround::itemAdd()
{
	ITEMMANAGER->itemAdd("item_1", type::DIRT_BLOCK, ItemType::BLOCK, "Item_1", 0);
	ITEMMANAGER->itemAdd("item_2", type::STONE_BLOCK, ItemType::BLOCK, "Item_2", 0);
	ITEMMANAGER->itemAdd("item_3", type::WOOD, ItemType::BLOCK, ItemType::METERIAL, "Item_3", 0);
	ITEMMANAGER->itemAdd("item_4", type::COPPER, ItemType::METERIAL, "Item_4", 0);
	ITEMMANAGER->itemAdd("item_5", type::COPPER_BAR, ItemType::METERIAL, "Item_5", 0);
	ITEMMANAGER->itemAdd("item_6", type::IRON, ItemType::METERIAL, "Item_6", 0);
	ITEMMANAGER->itemAdd("item_7", type::IRON_BAR, ItemType::METERIAL, "Item_7", 0);
	ITEMMANAGER->itemAdd("item_8", type::GOLD, ItemType::METERIAL, "Item_8", 0);
	ITEMMANAGER->itemAdd("item_9", type::GOLD_BAR, ItemType::METERIAL, "Item_9", 0);
	ITEMMANAGER->itemAdd("item_10", type::PLATINUM, ItemType::METERIAL, "Item_10", 0);
	ITEMMANAGER->itemAdd("item_11", type::PLATINUM_BAR, ItemType::METERIAL, "Item_11", 0);
	ITEMMANAGER->itemAdd("item_12", type::DEMONITE, ItemType::METERIAL, "Item_12", 0);
	ITEMMANAGER->itemAdd("item_13", type::DEMONITE_BAR, ItemType::METERIAL, "Item_13", 0);

	ITEMMANAGER->itemAdd("item_14", type::COPPER_PICKAXE, ItemType::PICKAXE, "Item_14", 0, 4);
	ITEMMANAGER->itemAdd("item_15", type::COPPER_AXE, ItemType::AXE, "Item_15", 0, 3);
	ITEMMANAGER->itemAdd("item_16", type::COPPER_HAMMER, ItemType::HAMMER, "Item_16", 0, 4);
	ITEMMANAGER->itemAdd("item_17", type::COPPER_SWORD, ItemType::SWORD, "Item_16", 0, 8);

	ITEMMANAGER->itemAdd("item_18", type::IRON_PICKAXE, ItemType::PICKAXE, "Item_18", 0, 5);
	ITEMMANAGER->itemAdd("item_19", type::IRON_AXE, ItemType::AXE, "Item_19", 0, 5);
	ITEMMANAGER->itemAdd("item_20", type::IRON_HAMMER, ItemType::HAMMER, "Item_20", 0, 7);
	ITEMMANAGER->itemAdd("item_21", type::IRON_SWORD, ItemType::SWORD, "Item_21", 0, 10);

	ITEMMANAGER->itemAdd("item_22", type::GOLD_PICKAXE, ItemType::PICKAXE, "Item_22", 0, 6);
	ITEMMANAGER->itemAdd("item_23", type::GOLD_AXE, ItemType::AXE, "Item_23", 0, 7);
	ITEMMANAGER->itemAdd("item_24", type::GOLD_HAMMER, ItemType::HAMMER, "Item_24", 0, 9);
	ITEMMANAGER->itemAdd("item_25", type::GOLD_SWORD, ItemType::SWORD, "Item_25", 0, 13);

	ITEMMANAGER->itemAdd("item_26", type::PLATINUM_PICKAXE, ItemType::PICKAXE, "Item_26", 0, 7);
	ITEMMANAGER->itemAdd("item_27", type::PLATINUM_AXE, ItemType::AXE, "Item_27", 0, 8);
	ITEMMANAGER->itemAdd("item_28", type::PLATINUM_HAMMER, ItemType::HAMMER, "Item_28", 0, 10);
	ITEMMANAGER->itemAdd("item_29", type::PLATINUM_SWORD, ItemType::SWORD, "Item_29", 0, 15);

	ITEMMANAGER->itemAdd("item_30", type::DEMONITE_PICKAXE, ItemType::PICKAXE, "Item_30", 0, 9);
	ITEMMANAGER->itemAdd("item_31", type::DEMONITE_AXE, ItemType::AXE, "Item_31", 0, 20);
	ITEMMANAGER->itemAdd("item_32", type::DEMONITE_HAMMER, ItemType::HAMMER, "Item_32", 0, 24);
	ITEMMANAGER->itemAdd("item_33", type::DEMONITE_SWORD, ItemType::SWORD, "Item_33", 0, 17);

	ITEMMANAGER->itemAdd("item_34", type::COPPER_HELMET, ItemType::HELMET, "Item_34", 0, 1);
	ITEMMANAGER->itemAdd("item_35", type::COPPER_ARMOR, ItemType::ARMOR, "Item_35", 0, 2);
	ITEMMANAGER->itemAdd("item_36", type::COPPER_LEGGINGS, ItemType::LEGGINGS, "Item_36", 0, 1);

	ITEMMANAGER->itemAdd("item_37", type::IRON_HELMET, ItemType::HELMET, "Item_37", 0, 2);
	ITEMMANAGER->itemAdd("item_38", type::IRON_ARMOR, ItemType::ARMOR, "Item_38", 0, 3);
	ITEMMANAGER->itemAdd("item_39", type::IRON_LEGGINGS, ItemType::LEGGINGS, "Item_39", 0, 2);

	ITEMMANAGER->itemAdd("item_40", type::GOLD_HELMET, ItemType::HELMET, "Item_40", 0, 4);
	ITEMMANAGER->itemAdd("item_41", type::GOLD_ARMOR, ItemType::ARMOR, "Item_41", 0, 5);
	ITEMMANAGER->itemAdd("item_42", type::GOLD_LEGGINGS, ItemType::LEGGINGS, "Item_42", 0, 4);

	ITEMMANAGER->itemAdd("item_43", type::PLATINUM_HELMET, ItemType::HELMET, "Item_43", 0, 5);
	ITEMMANAGER->itemAdd("item_44", type::PLATINUM_ARMOR, ItemType::ARMOR, "Item_44", 0, 6);
	ITEMMANAGER->itemAdd("item_45", type::PLATINUM_LEGGINGS, ItemType::LEGGINGS, "Item_45", 0, 5);

	ITEMMANAGER->itemAdd("item_46", type::DEMONITE_HELMET, ItemType::HELMET, "Item_46", 0, 6);
	ITEMMANAGER->itemAdd("item_47", type::DEMONITE_ARMOR, ItemType::ARMOR, "Item_47", 0, 7);
	ITEMMANAGER->itemAdd("item_48", type::DEMONITE_LEGGINGS, ItemType::LEGGINGS, "Item_48", 0, 6);

	ITEMMANAGER->itemAdd("item_49", type::COPPER_COIN, ItemType::COIN, "Item_49", 0);
	ITEMMANAGER->itemAdd("item_50", type::IRON_COIN, ItemType::COIN, "Item_50", 0);
	ITEMMANAGER->itemAdd("item_51", type::GOLD_COIN, ItemType::COIN, "Item_51", 0);
	ITEMMANAGER->itemAdd("item_52", type::PLATINUM_COIN, ItemType::COIN, "Item_52", 0);

	ITEMMANAGER->itemAdd("item_53", type::DESK, ItemType::BLOCK, "Item_53", 0);
	ITEMMANAGER->itemAdd("item_54", type::FURNACE, ItemType::BLOCK, "Item_54", 0);
	ITEMMANAGER->itemAdd("item_55", type::WORKBENCH, ItemType::BLOCK, "Item_55", 0);
	ITEMMANAGER->itemAdd("item_56", type::ANVIL, ItemType::BLOCK, "Item_56", 0);
	ITEMMANAGER->itemAdd("item_57", type::CHIR, ItemType::BLOCK, "Item_57", 0);
	ITEMMANAGER->itemAdd("item_58", type::BOX, ItemType::BLOCK, "Item_58", 0);
	ITEMMANAGER->itemAdd("item_59", type::DOOR, ItemType::BLOCK, "Item_59", 0);
	ITEMMANAGER->itemAdd("item_60", type::WOOD_WALL, ItemType::WALL, "Item_60", 0);
	ITEMMANAGER->itemAdd("item_61", type::GEL, ItemType::METERIAL, "Item_61", 0);
	ITEMMANAGER->itemAdd("item_62", type::LENS, ItemType::METERIAL, "Item_62", 0);
	ITEMMANAGER->itemAdd("item_63", type::DEMONEYE, ItemType::CONSUMBLE, "Item_63", 0);
	ITEMMANAGER->itemAdd("item_64", type::POTION50, ItemType::CONSUMBLE, "Item_64", 0, 50);
	ITEMMANAGER->itemAdd("item_65", type::POTION100, ItemType::CONSUMBLE, "Item_65", 0, 100);
	ITEMMANAGER->itemAdd("item_66", type::ACORN, ItemType::BLOCK, "Item_66", 0);
	ITEMMANAGER->itemAdd("item_67", type::HEARTCRYSTAL, ItemType::CONSUMBLE, "Item_67", 0);
}
