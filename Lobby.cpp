#include "stdafx.h"
#include "Lobby.h"

HRESULT Lobby::init()
{
	_lobbyImage = IMAGEMANAGER->addImage("LobbyImage", "Resources/Lobby/Lobby.bmp", 1280, 720, false, RGB(255, 0, 255));
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
			//게임시작 버튼
			if (PtInRect(&_button[0], _ptMouse))
			{

			}
			//맵툴 버튼
			else if (PtInRect(&_button[1], _ptMouse))
			{
				SCENEMANAGER->changeScene("MapToolScene");
			}
			//환경설정 버튼
			else if (PtInRect(&_button[2], _ptMouse))
			{

			}
			//종료 버튼
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
