#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ض�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
HRESULT playGround::init()
{
	gameNode::init(true);
	imageAdd();
	SCENEMANAGER->init();
	_scene = new Scene;
	_scene->init();

	return S_OK;
}

//�޸� ������ ����� �ض�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::release()
{
	gameNode::release();

}

//������ ����� �ض�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::update()
{
	gameNode::update();


	SCENEMANAGER->update();
}

//����� �׷���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	
	
	
	//===================================================
	//�� ���ߴ�
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imageAdd()
{
	//���������������������������������� �� �� �� ������������������������������������������������������������
	IMAGEMANAGER->addImage("LobbyImage", "Resources/Lobby/Lobby.bmp", 1280, 720, false, RGB(255, 0, 255));
	//�������������������������������������������������������������������������������������������������������

	//Ÿ �� �� �� ��
	IMAGEMANAGER->addFrameImage("Tiles_0", "Resources/Tiles/Tiles_0.bmp", 96, 64,3,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Tiles_1", "Resources/Tiles/Tiles_1.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlockTiles", "Resources/Tiles/BlockTiles.bmp", 256, 192, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WallTiles", "Resources/Tiles/WallTiles/bmp", 96, 48, 6, 3, true, RGB(255, 0, 255));
}
