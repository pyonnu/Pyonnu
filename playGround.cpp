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
	imageAdd();
	SCENEMANAGER->init();
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
	//==================================================
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	
	
	
	//===================================================
	//딱 말했다
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imageAdd()
{
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■로 비 이 미 지■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->addImage("LobbyImage", "Resources/Lobby/Lobby.bmp", 1280, 720, false, RGB(255, 0, 255));
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	//타 일 이 미 지
	IMAGEMANAGER->addFrameImage("Tiles_0", "Resources/Tiles/Tiles_0.bmp", 96, 64,3,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Tiles_1", "Resources/Tiles/Tiles_1.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlockTiles", "Resources/Tiles/BlockTiles.bmp", 256, 192, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WallTiles", "Resources/Tiles/WallTiles/bmp", 96, 48, 6, 3, true, RGB(255, 0, 255));
}
