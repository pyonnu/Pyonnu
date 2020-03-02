#include "stdafx.h"
#include "Lobby.h"

HRESULT Lobby::init()
{
	addImage();
	for (int i = 0;i < 2;i++)
	{
		_button[i] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + i * 100, 200, 50);
	}
	return S_OK;
}

void Lobby::release()
{
}

void Lobby::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
			//���ӽ��� ��ư
			if (PtInRect(&_button[0], _ptMouse))
			{
				CAMERAMANAGER->setCameraType(cameraType::WORLD);
				SCENEMANAGER->changeScene("World");
			}
			//���� ��ư
			else if (PtInRect(&_button[1], _ptMouse))
			{
				CAMERAMANAGER->setCameraType(cameraType::MAPTOOL);
				SCENEMANAGER->changeScene("MapToolScene");
			}
	}
	

}

void Lobby::render()
{
	_lobbyImage->render(getMemDC());
	for (int i = 0;i < 4;i++)
	{
		//Rectangle(getMemDC(), _button[i]);
	}
	TextOut(getMemDC(), _button[0].left+70, _button[0].top, "���� ����", strlen("���� ����"));
	TextOut(getMemDC(), _button[1].left+80, _button[1].top, "�� ����", strlen("�� ����"));
}

void Lobby::addImage()
{
	_lobbyImage = IMAGEMANAGER->findImage("LobbyImage");
}
