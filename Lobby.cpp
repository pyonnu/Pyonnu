#include "stdafx.h"
#include "Lobby.h"

HRESULT Lobby::init()
{
	_lobbyImage = IMAGEMANAGER->addImage("LobbyImage","Resources/Lobby/Lobby.bmp",1280,720,false,RGB(255,0,255));
	return S_OK;
}

void Lobby::release()
{
}

void Lobby::update()
{
}

void Lobby::render()
{
}
