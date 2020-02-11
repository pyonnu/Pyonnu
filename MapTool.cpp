#include "stdafx.h"
#include "MapTool.h"

void setWindowsSize(int x, int y, int width, int height);

HRESULT MapTool::init()
{
	POINT size;
	size.x = MaxTile_X * TILESIZE;
	size.y = MaxTile_Y * TILESIZE;
	CAMERAMANAGER->setCameraSize(size);

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
			_Tile[x][y].blockType = BlockType::NONE;
			_Tile[x][y].wallType = WallType::NONE;
			_vTile.push_back(&_Tile[x][y]);
		}
	}
	Load();

	for (int x = 0;x < MaxBlockTile_X;x++)
	{
		for (int y = 0;y < MaxBlockTile_Y;y++)
		{
			_blockTile[x][y].rc = RectMake(1280 + x * 40, y * 40, 40, 40);
			_blockTile[x][y].FrameX = x;
			_blockTile[x][y].FrameY = y;
		}
	}

	_selectTile.FrameX = 0;
	_selectTile.FrameY = 0;
	_selectTile.Select = false;
	_selectTile.SelectTileType = TileType::BLOCK;

	_TileUI = RectMake(1280, 0, 320, 32 * MaxBlockTile_Y);

	ButtonInit();

	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
	CameraControl();

	selectTile();


	drawTile();

	changeTileList();

}

void MapTool::render()
{
	draw();
}

void MapTool::draw()
{
	CAMERAMANAGER->render();
	RECT temp;
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
	//버튼 출력-------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0;i < 10;i++)
	{
		Rectangle(CAMERAMANAGER->getbackDC(), _button[i]);
	}
	TextOut(CAMERAMANAGER->getbackDC(), (_button[0].left + _button[0].right) / 2 - 8, (_button[0].top + _button[0].bottom) / 2 - 8, "▲", strlen("▲"));
	TextOut(CAMERAMANAGER->getbackDC(), (_button[1].left + _button[1].right) / 2 - 8, (_button[1].top + _button[1].bottom) / 2 - 8, "▼", strlen("▼"));
	TextOut(CAMERAMANAGER->getbackDC(), (_button[2].left + _button[2].right) / 2 - 8, (_button[2].top + _button[2].bottom) / 2 - 8, "◀", strlen("◀"));
	TextOut(CAMERAMANAGER->getbackDC(), (_button[3].left + _button[3].right) / 2 - 8, (_button[3].top + _button[3].bottom) / 2 - 8, "▶", strlen("▶"));

	Rectangle(CAMERAMANAGER->getbackDC(), _TileUI);
	//----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int x = 0;x < MaxBlockTile_X;x++)
	{
		for (int y = 0; y < MaxBlockTile_Y; y++)
		{
			Rectangle(CAMERAMANAGER->getbackDC(), _blockTile[x][y].rc);
			IMAGEMANAGER->findImage("BlockTiles")->frameRender(CAMERAMANAGER->getbackDC(), _blockTile[x][y].rc.left, _blockTile[x][y].rc.top, _blockTile[x][y].FrameX, _blockTile[x][y].FrameY);

		}
	}
}

void MapTool::ButtonInit()
{
	_button[0] = RectMakeCenter(1440, 640, 40, 40);		//UP
	_button[1] = RectMakeCenter(1440, 690, 40, 40);		//DOWN
	_button[2] = RectMakeCenter(1390, 690, 40, 40);		//LEFT
	_button[3] = RectMakeCenter(1490, 690, 40, 40);		//RIGHT
	_button[4] = RectMakeCenter(1280, 800, 90, 40);		//Player select
	_button[5] = RectMakeCenter(1296, 600, 48, 20);		//Enemy  select
	//_button[6] = RectMakeCenter();						//Wall   select
	//_button[7] = RectMakeCenter();						//Block	 select
	//_button[8] = RectMakeCenter();						//Obejct select
}

void MapTool::CameraControl()
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
	CAMERAMANAGER->setCameraPos(_CameraPositon.x, _CameraPositon.y);
}

void MapTool::changeTileList()
{
	switch (_selectTile.SelectTileType)
	{
	case TileType::PLAYER:
		break;
	case TileType::ENEMY:
		break;
	case TileType::WALL:
		break;
	case TileType::BLOCK:
		break;
	case TileType::OBJECT:
		break;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//if (PtInRect(&_button[], _ptMouse))
		{

		}
	}
}

void MapTool::selectTile()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			for (int y = 0;y < MaxBlockTile_Y;y++)
			{
				if (PtInRect(&_blockTile[x][y].rc, _ptMouse))
				{
					_selectTile.Select = true;
					_selectTile.FrameX = x;
					_selectTile.FrameY = y;
				}
			}
		}
	}
}

void MapTool::drawTile()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int x = 0;x < MaxTile_X;x++)
		{
			for (int y = 0;y < MaxTile_Y;y++)
			{
				if (PtInRect(&_Tile[x][y].rc, _ptMouse))
				{
					_Tile[x][y].blockType;
				}
			}
		}
	}
}

void MapTool::Save()
{

}

void MapTool::Load()
{

}
