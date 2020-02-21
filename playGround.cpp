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
}

//여기다 그려라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

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
	//플레이어 이미지
	IMAGEMANAGER->addFrameImage("Player_Head", "Resources/Player/Player_Head.bmp", 80 * 2, 2 * 1120, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Player_Body", "Resources/Player/Player_Body.bmp", 80 * 2, 2 * 1120, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Player_Legs", "Resources/Player/Player_Legs.bmp", 80 * 2, 2 * 1120, 2, 20, true, RGB(255, 0, 255));
	//갑옷 이미지

	//UI이미지
	IMAGEMANAGER->addImage("Inventory_Back", "Resources/UI/Inventory_Back.bmp", 104, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Heart", "Resources/UI/Heart.bmp", 44, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ButtonDelete", "Resources/UI/ButtonDelete.bmp", 44, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_0", "Resources/UI/Craft_Toggle_0.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_1", "Resources/UI/Craft_Toggle_1.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_2", "Resources/UI/Craft_Toggle_2.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Craft_Toggle_3", "Resources/UI/Craft_Toggle_3.bmp", 60, 60, true, RGB(255, 0, 255));
	//Item이미지
	IMAGEMANAGER->addImage("Item_0", "Resources/Item/Item_0.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_1", "Resources/Item/Item_1.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_2", "Resources/Item/Item_2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_3", "Resources/Item/Item_3.bmp", 48, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_4", "Resources/Item/Item_4.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_5", "Resources/Item/Item_5.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_6", "Resources/Item/Item_6.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_7", "Resources/Item/Item_7.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_8", "Resources/Item/Item_8.bmp", 60, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_9", "Resources/Item/Item_9.bmp", 60, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_10", "Resources/Item/Item_10.bmp", 60, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_11", "Resources/Item/Item_11.bmp", 60, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_12", "Resources/Item/Item_12.bmp", 60, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_13", "Resources/Item/Item_13.bmp", 60, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_14", "Resources/Item/Item_14.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_15", "Resources/Item/Item_15.bmp", 64, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_16", "Resources/Item/Item_16.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_17", "Resources/Item/Item_17.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_18", "Resources/Item/Item_18.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_19", "Resources/Item/Item_19.bmp", 64, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_20", "Resources/Item/Item_20.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_21", "Resources/Item/Item_21.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_22", "Resources/Item/Item_22.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_23", "Resources/Item/Item_23.bmp", 64, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_24", "Resources/Item/Item_24.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_25", "Resources/Item/Item_25.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_26", "Resources/Item/Item_26.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_27", "Resources/Item/Item_27.bmp", 64, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_28", "Resources/Item/Item_28.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_29", "Resources/Item/Item_29.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_30", "Resources/Item/Item_30.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_31", "Resources/Item/Item_31.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_32", "Resources/Item/Item_32.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_33", "Resources/Item/Item_33.bmp", 72, 72, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_34", "Resources/Item/Item_34.bmp", 48, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_35", "Resources/Item/Item_35.bmp", 60, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_36", "Resources/Item/Item_36.bmp", 44, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_37", "Resources/Item/Item_37.bmp", 44, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_38", "Resources/Item/Item_38.bmp", 60, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_39", "Resources/Item/Item_39.bmp", 44, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_40", "Resources/Item/Item_40.bmp", 52, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_41", "Resources/Item/Item_41.bmp", 60, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_42", "Resources/Item/Item_42.bmp", 44, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_43", "Resources/Item/Item_43.bmp", 48, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_44", "Resources/Item/Item_44.bmp", 60, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_45", "Resources/Item/Item_45.bmp", 44, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_46", "Resources/Item/Item_46.bmp", 48, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_47", "Resources/Item/Item_47.bmp", 52, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_48", "Resources/Item/Item_48.bmp", 44, 36, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_49", "Resources/Item/Item_49.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_50", "Resources/Item/Item_50.bmp", 24, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_51", "Resources/Item/Item_51.bmp", 24, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_52", "Resources/Item/Item_52.bmp", 28, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_53", "Resources/Item/Item_53.bmp", 60, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_54", "Resources/Item/Item_54.bmp", 60, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_55", "Resources/Item/Item_55.bmp", 64, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_56", "Resources/Item/Item_56.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_57", "Resources/Item/Item_57.bmp", 32, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Item_58", "Resources/Item/Item_58.bmp", 64, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_59", "Resources/Item/Item_59.bmp", 36, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_60", "Resources/Item/Item_60.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_61", "Resources/Item/Item_61.bmp", 32, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_62", "Resources/Item/Item_62.bmp", 32, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_63", "Resources/Item/Item_63.bmp", 60, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_64", "Resources/Item/Item_64.bmp", 40, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_65", "Resources/Item/Item_65.bmp", 40, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_66", "Resources/Item/Item_66.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Item_67", "Resources/Item/Item_67.bmp", 44, 44, true, RGB(255, 0, 255));


}
