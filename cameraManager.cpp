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
	_cameraSize.x = 1600;
	_cameraSize.y = 900;
	_x = 0;
	_y = 0;
	HDC hdc2 = GetDC(_hWnd);
	_testDC = CreateCompatibleDC(hdc2);
	_testBit = (HBITMAP)CreateCompatibleBitmap(hdc2, 640, _cameraSize.y );
	_oldTestBit=(HBITMAP)SelectObject(_testDC, _testBit);

	HDC hdc = GetDC(_hWnd);
	_cameraDC = CreateCompatibleDC(hdc);	// 빈 DC영역 하나를 만든다
	_hbit= (HBITMAP)CreateCompatibleBitmap(hdc, 960,_cameraSize.y);
	_oldHbit= (HBITMAP)SelectObject(_cameraDC, _hbit);
	return S_OK;
}

void cameraManager::release()
{
	SelectObject(_cameraDC, _oldHbit);
	DeleteObject(_hbit);
	DeleteDC(_cameraDC);
	SelectObject(_testDC, _oldTestBit);
	DeleteObject(_testBit);
	DeleteDC(_testDC);
}

void cameraManager::render()
{
	BitBlt(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), 0, 0,
		960, _cameraSize.y,_cameraDC, _x,_y, WHITENESS);
	BitBlt(IMAGEMANAGER->findImage("backBuffer")->getMemDC(), 960, 0, 640, _cameraSize.y, _testDC,0,0,SRCCOPY);
}

void cameraManager::setCameraPos(float x, float y)
{
	_x = x - WINSIZEX / 2;
	_y = y - WINSIZEY / 2;
	if (_x <= 0)_x = 0;
	if (_y <= 0)_y = 0;
	if (_x + WINSIZEX >= IMAGEMANAGER->findImage("backBuffer")->getWidth())
	{ 
		_x = IMAGEMANAGER->findImage("backBuffer")->getWidth() - WINSIZEX;
	}	
	if (_y + WINSIZEY >= IMAGEMANAGER->findImage("backBuffer")->getHeight())
	{
		_y = IMAGEMANAGER->findImage("backBuffer")->getHeight() - WINSIZEY;
	}
}
