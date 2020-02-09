#include "stdafx.h"
#include "Lobby.h"

HRESULT Lobby::init()
{
	addImage();
	for (int i = 0;i < 4;i++)
	{
		_button[i] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 100 + i * 100, 200, 50);
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

			}
			//���� ��ư
			else if (PtInRect(&_button[1], _ptMouse))
			{
				SCENEMANAGER->changeScene("MapToolScene");
			}
			//ȯ�漳�� ��ư
			else if (PtInRect(&_button[2], _ptMouse))
			{

			}
			//���� ��ư
			else if (PtInRect(&_button[4], _ptMouse))
			{

			}
	}
	

}

void Lobby::render()
{
	_lobbyImage->render(getMemDC());
	for (int i = 0;i < 4;i++)
	{
		Rectangle(getMemDC(), _button[i]);
	}
}

void Lobby::addImage()
{
	_lobbyImage = IMAGEMANAGER->addImage("LobbyImage", "Resources/Lobby/Lobby.bmp", 1280, 720, false, RGB(255, 0, 255));
}
