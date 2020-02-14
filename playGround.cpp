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
	IMAGEMANAGER->addImage("임시Background_1", "Resources/BackGrounds/임시Background_1.bmp", 7680, 2880, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_2", "Resources/BackGrounds/Background_2.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_3", "Resources/BackGrounds/Background_3.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_4", "Resources/BackGrounds/Background_4.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_5", "Resources/BackGrounds/Backgorund_5.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_6", "Resources/BackGrounds/Backgorund_6.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_7", "Resources/BackGrounds/Backgorund_7.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_8", "Resources/BackGrounds/Backgorund_8.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_9", "Resources/BackGrounds/Backgorund_9.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background_10", "Resources/BackGrounds/Backgorund_10.bmp", 3840, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Background1", "Resources/BackGrounds/Background1.bmp", 1280, 2987, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Background2", "Resources/BackGrounds/Background2.bmp", 1280, 2987, 1, 4, true, RGB(255, 0, 255));
	//플레이어 이미지
	IMAGEMANAGER->addFrameImage("Player_Head", "Resources/Player/Player_Head.bmp", 80, 1120, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Player_Body", "Resources/Player/Player_Body.bmp", 80, 1120, 2, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Player_Legs", "Resources/Player/Player_Legs.bmp", 80, 1120, 2, 20, true, RGB(255, 0, 255));
	//갑옷 이미지


}
