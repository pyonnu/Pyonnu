#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	_cameraSize.x = 6400;
	_cameraSize.y = 14400;
	_pos.x = 0;
	_pos.y = 0;
	HDC hdc2 = GetDC(_hWnd);
	_backDC = CreateCompatibleDC(hdc2);
	_backHDCBit = (HBITMAP)CreateCompatibleBitmap(hdc2, 1600, 900);
	_oldBackHDCBit = (HBITMAP)SelectObject(_backDC, _backHDCBit);

	HDC hdc = GetDC(_hWnd);
	_cameraDC = CreateCompatibleDC(hdc);	// 빈 DC영역 하나를 만든다
	_hbit = (HBITMAP)CreateCompatibleBitmap(hdc, _cameraSize.x, _cameraSize.y);
	_oldHbit = (HBITMAP)SelectObject(_cameraDC, _hbit);	switch (_cameraType)

	_cameraSizeRect = RectMake(_pos.x, _pos.y, 1280, 720);

	return S_OK;
}

void cameraManager::release()
{
	SelectObject(_cameraDC, _oldHbit);
	DeleteObject(_hbit);
	DeleteDC(_cameraDC);
	SelectObject(_backDC, _oldBackHDCBit);
	DeleteObject(_backHDCBit);
	DeleteDC(_backDC);
}

void cameraManager::render()
{
	switch (_cameraType)
	{
	case cameraType::MAPTOOL:
		BitBlt(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), 0, 0, 1600, 900, _backDC, 0, 0, SRCCOPY);
		BitBlt(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), 0, 0, 1280,720, _cameraDC, _pos.x, _pos.y, SRCCOPY);
		break;
	case cameraType::PLAY:
		break;
	case cameraType::OPTION:
		break;
	}

}

void cameraManager::setCameraPos(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
	if (_pos.x <= 0)
	{
		_pos.x = 0;

	}
	if (_pos.y <= 0)
	{
		_pos.y = 0;

	}
	if (_pos.x + WINSIZEX >= _cameraSize.x)
	{ 
		_pos.x = _cameraSize.x - WINSIZEX;

	}	
	if (_pos.y + WINSIZEY >= _cameraSize.y)
	{
		_pos.y = _cameraSize.y - WINSIZEY;

	}
	_cameraSizeRect=RectMake(_pos.x, _pos.y, 1280, 720);
}


