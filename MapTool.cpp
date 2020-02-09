#include "stdafx.h"
#include "MapTool.h"

void setWindowsSize(int x, int y, int width, int height);

HRESULT MapTool::init()
{
	_winsize.x = 1600;
	_winsize.y = 900;
	setWindowsSize(WINSTARTX, WINSTARTY, _winsize.x, _winsize.y);
	_backBuffer->init(_winsize.x, _winsize.y);
	CAMERAMANAGER->init();
	_CameraPositon.x = _CameraPositon.y = 0;
	for (int x = 0;x < MaxTile_X;x++)
	{
		for (int y = 0;y < MaxTile_Y;y++)
		{
			_Tile[x][y].idx = x;
			_Tile[x][y].idy = y;
			_Tile[x][y].x = x * TILESIZE;
			_Tile[x][y].y = y * TILESIZE;
			_Tile[x][y].rc = RectMake(x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE);
			_Tile[x][y].tileType = TileType::WALL;
			_Tile[x][y].blockType = BlockType::NONE;
			_Tile[x][y].wallType = WallType::NONE;
			_vTile.push_back(&_Tile[x][y]);
		}
	}
	_TileUI = RectMake(1280, 0, 320, 576);

	_button[0] = RectMakeCenter(1440, 640, 40, 40);		//UP
	_button[1] = RectMakeCenter(1440, 690, 40, 40);		//DOWN
	_button[2] = RectMakeCenter(1390, 690, 40, 40);		//LEFT
	_button[3] = RectMakeCenter(1490, 690, 40, 40);		//RIGHT
	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_CameraPositon.y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_CameraPositon.y += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_CameraPositon.x -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_CameraPositon.x += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//UP
		if (PtInRect(&_button[0], _ptMouse))
		{
			_CameraPositon.y -= 5;
		}
		//DOWN
		if (PtInRect(&_button[1], _ptMouse))
		{
			_CameraPositon.y += 5;
		}
		//LEFT
		if (PtInRect(&_button[2], _ptMouse))
		{
			_CameraPositon.x -= 5;
		}
		//RIGHT
		if (PtInRect(&_button[3], _ptMouse))
		{
			_CameraPositon.x += 5;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

	}
	CAMERAMANAGER->setCameraPos(_CameraPositon.x, _CameraPositon.y);
}

void MapTool::render()
{
	RECT temp;
	CAMERAMANAGER->render();
	/*for (_viTile = _vTile.begin();_viTile != _vTile.end();++_viTile)
	{
		if (IntersectRect(&temp, &(*_viTile)->rc, &CAMERAMANAGER->getCameraRect()))
		{
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldbrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), brush);
			Rectangle(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc);
			SelectObject(CAMERAMANAGER->getCameraDC(), oldbrush);
			DeleteObject(brush);
		}
		else
		{
			continue;
		}
	}*/

	for (int x = 0;x < MaxTile_X;x++)
	{
		for (int y = 0;y < MaxTile_Y;y++)
		{
			if (IntersectRect(&temp, &_Tile[x][y].rc, &CAMERAMANAGER->getCameraRect()))
			{
				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH oldbrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), brush);
				Rectangle(CAMERAMANAGER->getCameraDC(), _Tile[x][y].rc);
				SelectObject(CAMERAMANAGER->getCameraDC(), oldbrush);
				DeleteObject(brush);
			}
		}
	}
	for (int i = 0;i < 10;i++)
	{
		Rectangle(CAMERAMANAGER->getbackDC(), _button[i]);
	}
	TextOut(CAMERAMANAGER->getbackDC(), (_button[0].left + _button[0].right) / 2 - 8, (_button[0].top + _button[0].bottom) / 2 - 8, "¡ã", strlen("¡ã"));
	TextOut(CAMERAMANAGER->getbackDC(), (_button[1].left + _button[1].right) / 2 - 8, (_button[1].top + _button[1].bottom) / 2 - 8, "¡å", strlen("¡å"));
	TextOut(CAMERAMANAGER->getbackDC(), (_button[2].left + _button[2].right) / 2 - 8, (_button[2].top + _button[2].bottom) / 2 - 8, "¢¸", strlen("¢¸"));
	TextOut(CAMERAMANAGER->getbackDC(), (_button[3].left + _button[3].right) / 2 - 8, (_button[3].top + _button[3].bottom) / 2 - 8, "¢º", strlen("¢º"));
	Rectangle(CAMERAMANAGER->getbackDC(), _TileUI);
	//RECT rc = RectMake(0, 0, 16, 16);
	//HBRUSH brush = CreateSolidBrush(RGB(0,255,0));
	//HBRUSH oldbrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), brush);
	//Rectangle(CAMERAMANAGER->getCameraDC(), rc);
	//SelectObject(CAMERAMANAGER->getCameraDC(), oldbrush);
	//DeleteObject(brush);
}
