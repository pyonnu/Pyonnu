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
			_Tile[x][y].FrameX = 0;
			_Tile[x][y].FrameY = 0;
			_Tile[x][y].FrameX2 = 0;
			_Tile[x][y].FrameY2 = 0;
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
			_UITile[x][y].rc = RectMake(1280 + x * 40, y * 40, 40, 40);
			_UITile[x][y].FrameX = x;
			_UITile[x][y].FrameY = y;
		}
	}
	
	


	_selectTile.FrameX = 0;
	_selectTile.FrameY = 0;
	_selectTile.Select = false;
	_selectTile.SelectTileType = TileType::BLOCK;

	_TileUI = RectMake(1280, 0, 320, 32 * MaxBlockTile_Y);

	blockTileInit();
	ButtonInit();

	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
	CameraControl();
	blockTileInit();

	selectTile();
	drawTile();

	changeTileList();
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		Save();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		Load();
	}
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
				//Rectangle(CAMERAMANAGER->getCameraDC(), _Tile[x][y].rc);
				IMAGEMANAGER->findImage("WallTiles")->frameRender(CAMERAMANAGER->getCameraDC(), _Tile[x][y].rc.left, _Tile[x][y].rc.top, _Tile[x][y].FrameX2, _Tile[x][y].FrameY2);
				IMAGEMANAGER->findImage("BlockTiles")->frameRender(CAMERAMANAGER->getCameraDC(), _Tile[x][y].rc.left, _Tile[x][y].rc.top, _Tile[x][y].FrameX, _Tile[x][y].FrameY);
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
			Rectangle(CAMERAMANAGER->getbackDC(), _UITile[x][y].rc);
		}
	}
	switch (_selectTile.SelectTileType)
	{
	case TileType::PLAYER:
		break;
	case TileType::ENEMY:
		break;
	case TileType::WALL:
	case TileType::BLOCK:
	case TileType::OBJECT:
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			for (int y = 0;y < MaxBlockTile_Y;y++)
			{
				IMAGEMANAGER->findImage("BlockTiles")->frameRender(CAMERAMANAGER->getbackDC(), _UITile[x][y].rc.left + 4, _UITile[x][y].rc.top + 4, x, y);
			}
		}
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			for (int y = 1;y < MaxBlockTile_Y;y++)
			{
				IMAGEMANAGER->findImage("WallTiles")->frameRender(CAMERAMANAGER->getbackDC(), _UITile[x][y].rc.left + 4, _UITile[x][y].rc.top + 4, x, y - 1);
			}
		}
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			for (int y = 2; y < MaxBlockTile_Y;y++)
			{
				IMAGEMANAGER->findImage("ObjectTiles")->frameRender(CAMERAMANAGER->getbackDC(), _UITile[x][y].rc.left + 4, _UITile[x][y].rc.top + 4, x, y - 2);
			}
		}
		break;
	case TileType::TREE:
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			for (int y = 0;y < MaxBlockTile_Y;y++)
			{
				IMAGEMANAGER->findImage("Tree")->frameRender(CAMERAMANAGER->getbackDC(), _UITile[x][y].rc.left + 4, _UITile[x][y].rc.top + 4, x, y);
			}
		}
		break;
	default:
		break;
	}

}

void MapTool::blockTileInit()
{
	switch (_selectTile.SelectTileType)
	{
	case TileType::PLAYER:
		break;
	case TileType::ENEMY:
		break;
	case TileType::WALL:
	case TileType::BLOCK:
	case TileType::OBJECT:
		_UITile[0][0].SetTileType = TileType::BLOCK;
		_UITile[1][0].SetTileType = TileType::BLOCK;
		_UITile[2][0].SetTileType = TileType::BLOCK;
		_UITile[3][0].SetTileType = TileType::BLOCK;
		_UITile[4][0].SetTileType = TileType::BLOCK;
		_UITile[5][0].SetTileType = TileType::BLOCK;
		_UITile[6][0].SetTileType = TileType::BLOCK;
		_UITile[7][0].SetTileType = TileType::BLOCK;

		_UITile[0][0].SetBlockType = BlockType::NONE;
		_UITile[1][0].SetBlockType = BlockType::DIRT;
		_UITile[2][0].SetBlockType = BlockType::STONE;
		_UITile[3][0].SetBlockType = BlockType::COPPER;
		_UITile[4][0].SetBlockType = BlockType::IRON;
		_UITile[5][0].SetBlockType = BlockType::GOLD;
		_UITile[6][0].SetBlockType = BlockType::PLATINUM;
		_UITile[7][0].SetBlockType = BlockType::WOOD;

		_UITile[0][1].SetTileType = TileType::WALL;
		_UITile[1][1].SetTileType = TileType::WALL;
		_UITile[2][1].SetTileType = TileType::WALL;
		_UITile[3][1].SetTileType = TileType::WALL;

		_UITile[0][1].SetWallType = WallType::NONE;
		_UITile[1][1].SetWallType = WallType::DIRT;
		_UITile[2][1].SetWallType = WallType::STONE;
		_UITile[3][1].SetWallType = WallType::WOOD;

		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			for (int y = 2;y < 8;y++)
			{
				_UITile[x][y].SetTileType = TileType::OBJECT;
			}
		}
		_UITile[6][4].SetObjectType = ObjectType::NONE;
		_UITile[6][5].SetObjectType = ObjectType::NONE;
		_UITile[3][6].SetObjectType = ObjectType::NONE;
		_UITile[4][6].SetObjectType = ObjectType::NONE;
		_UITile[5][6].SetObjectType = ObjectType::NONE;
		_UITile[6][6].SetObjectType = ObjectType::NONE;

		_UITile[0][2].SetObjectType = ObjectType::DESK;
		_UITile[1][2].SetObjectType = ObjectType::DESK;
		_UITile[2][2].SetObjectType = ObjectType::DESK;
		_UITile[0][3].SetObjectType = ObjectType::DESK;
		_UITile[1][3].SetObjectType = ObjectType::DESK;
		_UITile[2][3].SetObjectType = ObjectType::DESK;

		_UITile[3][2].SetObjectType = ObjectType::HEARTCRYSTAL;
		_UITile[4][2].SetObjectType = ObjectType::HEARTCRYSTAL;
		_UITile[3][3].SetObjectType = ObjectType::HEARTCRYSTAL;
		_UITile[4][3].SetObjectType = ObjectType::HEARTCRYSTAL;

		_UITile[5][2].SetObjectType = ObjectType::CHIR;
		_UITile[6][2].SetObjectType = ObjectType::CHIR;
		_UITile[5][3].SetObjectType = ObjectType::CHIR;
		_UITile[6][3].SetObjectType = ObjectType::CHIR;

		_UITile[0][4].SetObjectType = ObjectType::FURNACE;
		_UITile[1][4].SetObjectType = ObjectType::FURNACE;
		_UITile[2][4].SetObjectType = ObjectType::FURNACE;
		_UITile[0][5].SetObjectType = ObjectType::FURNACE;
		_UITile[1][5].SetObjectType = ObjectType::FURNACE;
		_UITile[2][5].SetObjectType = ObjectType::FURNACE;

		_UITile[3][4].SetObjectType = ObjectType::BOX;
		_UITile[4][4].SetObjectType = ObjectType::BOX;
		_UITile[3][5].SetObjectType = ObjectType::BOX;
		_UITile[4][5].SetObjectType = ObjectType::BOX;

		_UITile[5][4].SetObjectType = ObjectType::WORKBENCH;
		_UITile[6][4].SetObjectType = ObjectType::WORKBENCH;

		_UITile[5][5].SetObjectType = ObjectType::ANVIL;
		_UITile[6][5].SetObjectType = ObjectType::ANVIL;

		_UITile[0][6].SetObjectType = ObjectType::OPENDOOR;
		_UITile[1][6].SetObjectType = ObjectType::OPENDOOR;
		_UITile[0][7].SetObjectType = ObjectType::OPENDOOR;
		_UITile[1][7].SetObjectType = ObjectType::OPENDOOR;
		_UITile[0][8].SetObjectType = ObjectType::OPENDOOR;
		_UITile[1][8].SetObjectType = ObjectType::OPENDOOR;

		_UITile[2][6].SetObjectType = ObjectType::CLOSEDOOR;
		_UITile[2][7].SetObjectType = ObjectType::CLOSEDOOR;
		_UITile[2][8].SetObjectType = ObjectType::CLOSEDOOR;

		_UITile[3][6].SetObjectType = ObjectType::DEMONATLER;
		_UITile[4][6].SetObjectType = ObjectType::DEMONATLER;
		_UITile[5][6].SetObjectType = ObjectType::DEMONATLER;
		_UITile[3][7].SetObjectType = ObjectType::DEMONATLER;
		_UITile[4][7].SetObjectType = ObjectType::DEMONATLER;
		_UITile[5][7].SetObjectType = ObjectType::DEMONATLER;


		break;
	case TileType::TREE:
		for (int x = 0;x < 5;x++)
		{
			for (int y = 0;y < 10;y++)
			{
				_UITile[x][y].SetObjectType = ObjectType::TREE;
				for (int x = 5;x < 8;x++)
				{
					_UITile[x][y].SetObjectType = ObjectType::NONE;
				}
			}
			
		}
		
		break;
	default:
		break;
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

	if (_CameraPositon.x <= 0)
	{
		_CameraPositon.x = 0;
	}
	if (_CameraPositon.y <= 0)
	{
		_CameraPositon.y = 0;
	}
	if (_CameraPositon.x + WINSIZEX >= CAMERAMANAGER->getCameraSize().x)
	{
		_CameraPositon.x = CAMERAMANAGER->getCameraSize().x - WINSIZEX;
	}
	if (_CameraPositon.y + WINSIZEY >= CAMERAMANAGER->getCameraSize().y)
	{
		_CameraPositon.y = CAMERAMANAGER->getCameraSize().y - WINSIZEY;
	}

	CAMERAMANAGER->setCameraPos(_CameraPositon.x, _CameraPositon.y);
}

void MapTool::changeTileList()
{

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
				if (PtInRect(&_UITile[x][y].rc, _ptMouse))
				{
					switch (_UITile[x][y].SetTileType)
					{
					case TileType::PLAYER:
						break;
					case TileType::ENEMY:
						break;
					case TileType::WALL:
						wallFrameSet(x, y-1);
						break;
					case TileType::BLOCK:
						blockFrameSet(x, y);
						break;
					case TileType::OBJECT:
						objectFrameSet(x, y-2);
						break;
					case TileType::TREE:
						treeFrameSet(x, y);
						break;
					default:
						break;
					}
					
				}
			}
		}
	}
}

void MapTool::blockFrameSet(int x, int y)
{
	_selectTile.SelectTileType = TileType::BLOCK;
	switch (_UITile[x][y].SetBlockType)
	{
	case BlockType::NONE:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::DIRT:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::WOOD:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::STONE:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::COPPER:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::IRON:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::GOLD:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::PLATINUM:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	}
}

void MapTool::wallFrameSet(int x, int y)
{
	_selectTile.SelectTileType = TileType::WALL;
	switch (_UITile[x][y].SetWallType)
	{
	case WallType::NONE:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectWallType = _UITile[x][y].SetWallType;
		break;
	case WallType::DIRT:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectWallType = _UITile[x][y].SetWallType;
		break;
	case WallType::WOOD:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectWallType = _UITile[x][y].SetWallType;
		break;
	case WallType::STONE:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectWallType = _UITile[x][y].SetWallType;
		break;
	}
}

void MapTool::objectFrameSet(int x, int y)
{
	_selectTile.SelectTileType = TileType::OBJECT;
	switch (_UITile[x][y].SetObjectType)
	{
	case ObjectType::NONE:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::DEMONATLER:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::HEARTCRYSTAL:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::OPENDOOR:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::CLOSEDOOR:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::FURNACE:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::BOX:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::WORKBENCH:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::CHIR:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::DESK:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	case ObjectType::ANVIL:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
		break;
	}
}

void MapTool::treeFrameSet(int x, int y)
{
	_selectTile.SelectTileType = TileType::TREE;
	_selectTile.FrameX = x;
	_selectTile.FrameY = y;
	_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
}

void MapTool::drawTile()
{
	RECT rc;
	RECT temp;
	POINT start;
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		start = _ptMouse;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//start = _ptMouse;
		rc = RectMake(start.x, start.y, _ptMouse.x, _ptMouse.y);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		for (int x = 0;x < MaxTile_X;x++)
		{
			for (int y = 0;y < MaxTile_Y;y++)
			{
				if (IntersectRect(&temp,&_Tile[x][y].rc,&rc))
				{
					switch (_selectTile.SelectTileType)
					{
					case TileType::PLAYER:
						break;
					case TileType::ENEMY:
						break;
					case TileType::WALL:
						_Tile[x][y].wallType = _selectTile.SelectWallType;
						_Tile[x][y].FrameX2 = _selectTile.FrameX;
						_Tile[x][y].FrameY2 = _selectTile.FrameY;
						break;
					case TileType::BLOCK:
						_Tile[x][y].blockType = _selectTile.SelectBlockType;
						_Tile[x][y].FrameX = _selectTile.FrameX;
						_Tile[x][y].FrameY = _selectTile.FrameY;
						break;
					case TileType::OBJECT:
						_Tile[x][y].objectType = _selectTile.SelectObjectType;
						_Tile[x][y].FrameX3 = _selectTile.FrameX;
						_Tile[x][y].FrameY3 = _selectTile.FrameY;
						break;
					case TileType::TREE:
						_Tile[x][y].objectType = _selectTile.SelectObjectType;
						_Tile[x][y].FrameX3 = _selectTile.FrameX;
						_Tile[x][y].FrameY3 = _selectTile.FrameY;
						break;
					}

				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int x = 0;x < MaxTile_X;x++)
		{
			for (int y = 0;y < MaxTile_Y;y++)
			{
				if (PtInRect(&_Tile[x][y].rc, PointMake(_CameraPositon.x+_ptMouse.x,_CameraPositon.y+_ptMouse.y)))
				{
					switch (_selectTile.SelectTileType)
					{
					case TileType::PLAYER:
						break;
					case TileType::ENEMY:
						break;
					case TileType::WALL:
						_Tile[x][y].wallType = _selectTile.SelectWallType;
						_Tile[x][y].FrameX2 = _selectTile.FrameX;
						_Tile[x][y].FrameY2 = _selectTile.FrameY;
						break;
					case TileType::BLOCK:
						_Tile[x][y].blockType = _selectTile.SelectBlockType;
						_Tile[x][y].FrameX = _selectTile.FrameX;
						_Tile[x][y].FrameY = _selectTile.FrameY;
						break;
					case TileType::OBJECT:
						_Tile[x][y].objectType = _selectTile.SelectObjectType;
						_Tile[x][y].FrameX3 = _selectTile.FrameX;
						_Tile[x][y].FrameY3 = _selectTile.FrameY;
						break;
					case TileType::TREE:
						_Tile[x][y].objectType = _selectTile.SelectObjectType;
						_Tile[x][y].FrameX3 = _selectTile.FrameX;
						_Tile[x][y].FrameY3 = _selectTile.FrameY;
						break;
					}
					
				}
			}
		}
	}
	
}

void MapTool::Save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("SaveFile.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _Tile, sizeof(tagTile) * MaxTile_X * MaxTile_Y, &write, NULL);

	CloseHandle(file);
}

void MapTool::Load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다
	ReadFile(file, _Tile, sizeof(tagTile) * MaxTile_X * MaxTile_X, &read, NULL);

	CloseHandle(file);
}
