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
			_Tile[x][y].index.x = x;
			_Tile[x][y].index.y = y;
			_Tile[x][y].x = x * TILESIZE;
			_Tile[x][y].y = y * TILESIZE;
			_Tile[x][y].FrameX = 0;
			_Tile[x][y].FrameY = 0;
			_Tile[x][y].FrameX2 = 0;
			_Tile[x][y].FrameY2 = 0;
			_Tile[x][y].FrameX3 = 6;
			_Tile[x][y].FrameY3 = 6;
			_Tile[x][y].WORKBENCH = false;
			_Tile[x][y].ANVIL = false;
			_Tile[x][y].FURNACE = false;
			_Tile[x][y].DEMONALTER = false;
			_Tile[x][y].rc = RectMake(x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE);
			//_Tile[x][y].blockType = BlockType::NONE;
			//_Tile[x][y].wallType = WallType::NONE;
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

	_start = { 0,0 };

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
	//ButtonControl();
	//blockTileInit();
	selectTile();
	drawTile();
	//changeTileList();
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		Save();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		Load();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("LobbyScene");

	}
}

void MapTool::render()
{
	draw();
}

void MapTool::draw()
{
	PatBlt(CAMERAMANAGER->getbackDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	CAMERAMANAGER->render();

	//IMAGEMANAGER->findImage("Background1")->render(CAMERAMANAGER->getCameraDC(), _CameraPositon.x, _CameraPositon.y, _CameraPositon.x, _CameraPositon.y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("Background6")->render(CAMERAMANAGER->getCameraDC(), _CameraPositon.x, _CameraPositon.y);
	RECT temp;

	for (int x = 0;x < MaxTile_X;x++)
	{
		for (int y = 0;y < MaxTile_Y;y++)
		{
			if (IntersectRect(&temp, &_Tile[x][y].rc, &CAMERAMANAGER->getCameraRect()))
			{
				if ((_Tile[x][y].wallType != WallType::NONE&& _Tile[x][y].blockType == BlockType::NONE)
					||(_Tile[x][y].wallType != WallType::NONE && _Tile[x][y].objectType != ObjectType::NONE))

					IMAGEMANAGER->findImage("WallTiles")->frameRender(CAMERAMANAGER->getCameraDC(), 
						_Tile[x][y].rc.left, _Tile[x][y].rc.top, 
						_Tile[x][y].FrameX2, _Tile[x][y].FrameY2);

				if (_Tile[x][y].blockType != BlockType::NONE&& _Tile[x][y].objectType == ObjectType::NONE)

					IMAGEMANAGER->findImage("BlockTiles")->frameRender(CAMERAMANAGER->getCameraDC(), 
						_Tile[x][y].rc.left, _Tile[x][y].rc.top, 
						_Tile[x][y].FrameX, _Tile[x][y].FrameY);

				if (_Tile[x][y].objectType != ObjectType::NONE)

					IMAGEMANAGER->findImage("ObjectTiles")->frameRender(CAMERAMANAGER->getCameraDC(), 
						_Tile[x][y].rc.left, _Tile[x][y].rc.top,
						_Tile[x][y].FrameX3, _Tile[x][y].FrameY3);
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
	case TileType::BLOCK:
	case TileType::WALL:
	case TileType::OBJECT:
		//Block 초기화 =========================================
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			_UITile[x][0].SetTileType = TileType::BLOCK;
		}
		_UITile[0][0].SetBlockType = BlockType::NONE;
		_UITile[1][0].SetBlockType = BlockType::DIRT;
		_UITile[1][0].burglar = 50.0f;
		_UITile[2][0].SetBlockType = BlockType::STONE;
		_UITile[2][0].burglar = 100.0f;
		_UITile[3][0].SetBlockType = BlockType::COPPER;
		_UITile[3][0].burglar = 100.0f;
		_UITile[4][0].SetBlockType = BlockType::IRON;
		_UITile[4][0].burglar = 100.0f;
		_UITile[5][0].SetBlockType = BlockType::GOLD;
		_UITile[5][0].burglar = 100.0f;
		_UITile[6][0].SetBlockType = BlockType::PLATINUM;
		_UITile[6][0].burglar = 150.0f;
		_UITile[7][0].SetBlockType = BlockType::WOOD;
		_UITile[7][0].burglar = 100.0f;
		//Wall 초기화 ===============================================
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			_UITile[x][1].SetTileType = TileType::WALL;
		}
		_UITile[0][1].SetWallType = WallType::NONE;
		_UITile[1][1].SetWallType = WallType::DIRT;
		_UITile[1][1].burglar = 50.0f;
		_UITile[2][1].SetWallType = WallType::STONE;
		_UITile[2][1].burglar = 100.0f;
		_UITile[3][1].SetWallType = WallType::WOOD;
		_UITile[3][1].burglar = 100.0f;
		_UITile[4][1].SetWallType = WallType::NONE;
		_UITile[5][1].SetWallType = WallType::NONE;
		_UITile[6][1].SetWallType = WallType::NONE;
		_UITile[7][1].SetWallType = WallType::NONE;
		//Object 초기화 =============================================
		for (int x = 0;x < MaxBlockTile_X;x++)
		{
			for (int y = 2;y < MaxBlockTile_Y;y++)
			{
				_UITile[x][y].SetTileType = TileType::OBJECT;
				_UITile[x][y].burglar = 100.0f;
			}
		}
		_UITile[0][2].SetObjectType = ObjectType::DESK1;
		_UITile[1][2].SetObjectType = ObjectType::DESK2;
		_UITile[2][2].SetObjectType = ObjectType::DESK3;
		_UITile[3][2].SetObjectType = ObjectType::HEARTCRYSTAL1;
		_UITile[4][2].SetObjectType = ObjectType::HEARTCRYSTAL2;
		_UITile[5][2].SetObjectType = ObjectType::LEFTCHIR1;
		_UITile[6][2].SetObjectType = ObjectType::RIGHTCHIR1;
		_UITile[7][2].SetObjectType = ObjectType::NONE;
		_UITile[7][2].burglar = NULL;

		_UITile[0][3].SetObjectType = ObjectType::DESK4;
		_UITile[1][3].SetObjectType = ObjectType::DESK5;
		_UITile[2][3].SetObjectType = ObjectType::DESK6;
		_UITile[3][3].SetObjectType = ObjectType::HEARTCRYSTAL3;
		_UITile[4][3].SetObjectType = ObjectType::HEARTCRYSTAL4;
		_UITile[5][3].SetObjectType = ObjectType::LEFTCHIR2;
		_UITile[6][3].SetObjectType = ObjectType::RIGHTCHIR2;
		_UITile[7][3].SetObjectType = ObjectType::NONE;
		_UITile[7][3].burglar = NULL;

		_UITile[0][4].SetObjectType = ObjectType::FURNACE1;
		_UITile[1][4].SetObjectType = ObjectType::FURNACE2;
		_UITile[2][4].SetObjectType = ObjectType::FURNACE3;
		_UITile[3][4].SetObjectType = ObjectType::BOX1;
		_UITile[4][4].SetObjectType = ObjectType::BOX2;
		_UITile[5][4].SetObjectType = ObjectType::WORKBENCH1;
		_UITile[6][4].SetObjectType = ObjectType::WORKBENCH2;
		_UITile[7][4].SetObjectType = ObjectType::NONE;
		_UITile[7][4].burglar = NULL;

		_UITile[0][5].SetObjectType = ObjectType::FURNACE4;
		_UITile[1][5].SetObjectType = ObjectType::FURNACE5;
		_UITile[2][5].SetObjectType = ObjectType::FURNACE6;
		_UITile[3][5].SetObjectType = ObjectType::BOX3;
		_UITile[4][5].SetObjectType = ObjectType::BOX4;
		_UITile[5][5].SetObjectType = ObjectType::ANVIL1;
		_UITile[6][5].SetObjectType = ObjectType::ANVIL2;
		_UITile[7][5].SetObjectType = ObjectType::NONE;
		_UITile[7][5].burglar = NULL;

		_UITile[0][6].SetObjectType = ObjectType::RIGHT_OPENDOOR1;
		_UITile[1][6].SetObjectType = ObjectType::RIGHT_OPENDOOR2;
		_UITile[2][6].SetObjectType = ObjectType::CLOSEDOOR1;
		_UITile[3][6].SetObjectType = ObjectType::DEMONALTER1;
		_UITile[4][6].SetObjectType = ObjectType::DEMONALTER2;
		_UITile[5][6].SetObjectType = ObjectType::DEMONALTER3;
		_UITile[6][6].SetObjectType = ObjectType::NONE;
		_UITile[7][6].SetObjectType = ObjectType::NONE;
		_UITile[6][6].burglar = NULL;
		_UITile[7][6].burglar = NULL;

		_UITile[0][7].SetObjectType = ObjectType::RIGHT_OPENDOOR3;
		_UITile[1][7].SetObjectType = ObjectType::RIGHT_OPENDOOR4;
		_UITile[2][7].SetObjectType = ObjectType::CLOSEDOOR2;
		_UITile[3][7].SetObjectType = ObjectType::DEMONALTER4;
		_UITile[4][7].SetObjectType = ObjectType::DEMONALTER5;
		_UITile[5][7].SetObjectType = ObjectType::DEMONALTER6;
		_UITile[6][7].SetObjectType = ObjectType::NONE;
		_UITile[7][7].SetObjectType = ObjectType::NONE;
		_UITile[6][7].burglar = NULL;
		_UITile[7][7].burglar = NULL;

		_UITile[0][8].SetObjectType = ObjectType::RIGHT_OPENDOOR5;
		_UITile[1][8].SetObjectType = ObjectType::RIGHT_OPENDOOR6;
		_UITile[2][8].SetObjectType = ObjectType::CLOSEDOOR3;
		_UITile[3][8].SetObjectType = ObjectType::NONE;
		_UITile[4][8].SetObjectType = ObjectType::NONE;
		_UITile[5][8].SetObjectType = ObjectType::NONE;
		_UITile[6][8].SetObjectType = ObjectType::NONE;
		_UITile[7][8].SetObjectType = ObjectType::NONE;
		_UITile[3][8].burglar = NULL;
		_UITile[4][8].burglar = NULL;
		_UITile[5][8].burglar = NULL;
		_UITile[6][8].burglar = NULL;
		_UITile[7][8].burglar = NULL;

		_UITile[0][9].SetObjectType = ObjectType::TREE1;
		_UITile[1][9].SetObjectType = ObjectType::TREE2;
		_UITile[2][9].SetObjectType = ObjectType::TREE3;
		_UITile[3][9].SetObjectType = ObjectType::TREE4;
		_UITile[4][9].SetObjectType = ObjectType::TREE5;
		_UITile[5][9].SetObjectType = ObjectType::LEFT_OPENDOOR1;
		_UITile[6][9].SetObjectType = ObjectType::LEFT_OPENDOOR2;
		_UITile[7][9].SetObjectType = ObjectType::NONE;
		_UITile[7][9].burglar = NULL;

		_UITile[0][10].SetObjectType = ObjectType::TREE6;
		_UITile[1][10].SetObjectType = ObjectType::TREE7;
		_UITile[2][10].SetObjectType = ObjectType::TREE8;
		_UITile[3][10].SetObjectType = ObjectType::TREE9;
		_UITile[4][10].SetObjectType = ObjectType::TREE10;
		_UITile[5][10].SetObjectType = ObjectType::LEFT_OPENDOOR3;
		_UITile[6][10].SetObjectType = ObjectType::LEFT_OPENDOOR4;
		_UITile[7][10].SetObjectType = ObjectType::NONE;
		_UITile[7][10].burglar = NULL;

		_UITile[0][11].SetObjectType = ObjectType::TREE11;
		_UITile[1][11].SetObjectType = ObjectType::TREE12;
		_UITile[2][11].SetObjectType = ObjectType::TREE13;
		_UITile[3][11].SetObjectType = ObjectType::TREE14;
		_UITile[4][11].SetObjectType = ObjectType::TREE15;
		_UITile[5][11].SetObjectType = ObjectType::LEFT_OPENDOOR5;
		_UITile[6][11].SetObjectType = ObjectType::LEFT_OPENDOOR6;
		_UITile[7][11].SetObjectType = ObjectType::NONE;
		_UITile[7][11].burglar = NULL;

		_UITile[0][12].SetObjectType = ObjectType::TREE16;
		_UITile[1][12].SetObjectType = ObjectType::TREE17;
		_UITile[2][12].SetObjectType = ObjectType::TREE18;
		_UITile[3][12].SetObjectType = ObjectType::TREE19;
		_UITile[4][12].SetObjectType = ObjectType::TREE20;
		_UITile[5][12].SetObjectType = ObjectType::NONE;
		_UITile[6][12].SetObjectType = ObjectType::NONE;
		_UITile[7][12].SetObjectType = ObjectType::NONE;
		_UITile[5][12].burglar = NULL;
		_UITile[6][12].burglar = NULL;
		_UITile[7][12].burglar = NULL;

		_UITile[0][13].SetObjectType = ObjectType::TREE21;
		_UITile[1][13].SetObjectType = ObjectType::TREE22;
		_UITile[2][13].SetObjectType = ObjectType::TREE23;
		_UITile[3][13].SetObjectType = ObjectType::TREE24;
		_UITile[4][13].SetObjectType = ObjectType::TREE25;
		_UITile[5][13].SetObjectType = ObjectType::NONE;
		_UITile[6][13].SetObjectType = ObjectType::NONE;
		_UITile[7][13].SetObjectType = ObjectType::NONE;
		_UITile[5][13].burglar = NULL;
		_UITile[6][13].burglar = NULL;
		_UITile[7][13].burglar = NULL;

		_UITile[0][14].SetObjectType = ObjectType::NONE;
		_UITile[1][14].SetObjectType = ObjectType::TREE26;
		_UITile[2][14].SetObjectType = ObjectType::TREE27;
		_UITile[3][14].SetObjectType = ObjectType::NONE;
		_UITile[4][14].SetObjectType = ObjectType::NONE;
		_UITile[5][14].SetObjectType = ObjectType::NONE;
		_UITile[6][14].SetObjectType = ObjectType::NONE;
		_UITile[7][14].SetObjectType = ObjectType::NONE;
		_UITile[0][14].burglar = NULL;
		_UITile[3][14].burglar = NULL;
		_UITile[4][14].burglar = NULL;
		_UITile[5][14].burglar = NULL;
		_UITile[6][14].burglar = NULL;
		_UITile[7][14].burglar = NULL;

		_UITile[0][15].SetObjectType = ObjectType::TREE28;
		_UITile[1][15].SetObjectType = ObjectType::TREE29;
		_UITile[2][15].SetObjectType = ObjectType::TREE30;
		_UITile[3][15].SetObjectType = ObjectType::TREE31;
		_UITile[4][15].SetObjectType = ObjectType::TREE32;
		_UITile[5][15].SetObjectType = ObjectType::NONE;
		_UITile[6][15].SetObjectType = ObjectType::NONE;
		_UITile[7][15].SetObjectType = ObjectType::NONE;
		_UITile[5][15].burglar = NULL;
		_UITile[6][15].burglar = NULL;
		_UITile[7][15].burglar = NULL;

		_UITile[0][16].SetObjectType = ObjectType::NONE;
		_UITile[1][16].SetObjectType = ObjectType::TREE33;
		_UITile[2][16].SetObjectType = ObjectType::TREE34;
		_UITile[3][16].SetObjectType = ObjectType::TREE35;
		_UITile[4][16].SetObjectType = ObjectType::TREE36;
		_UITile[5][16].SetObjectType = ObjectType::NONE;
		_UITile[6][16].SetObjectType = ObjectType::NONE;
		_UITile[7][16].SetObjectType = ObjectType::NONE;
		_UITile[0][16].burglar = NULL;
		_UITile[5][16].burglar = NULL;
		_UITile[6][16].burglar = NULL;
		_UITile[7][16].burglar = NULL;

		_UITile[0][17].SetObjectType = ObjectType::NONE;
		_UITile[1][17].SetObjectType = ObjectType::TREE37;
		_UITile[2][17].SetObjectType = ObjectType::TREE38;
		_UITile[3][17].SetObjectType = ObjectType::NONE;
		_UITile[4][17].SetObjectType = ObjectType::NONE;
		_UITile[5][17].SetObjectType = ObjectType::NONE;
		_UITile[6][17].SetObjectType = ObjectType::NONE;
		_UITile[7][17].SetObjectType = ObjectType::NONE;
		_UITile[0][17].burglar = NULL;
		_UITile[3][17].burglar = NULL;
		_UITile[4][17].burglar = NULL;
		_UITile[5][17].burglar = NULL;
		_UITile[6][17].burglar = NULL;
		_UITile[7][17].burglar = NULL;

		_UITile[0][18].SetObjectType = ObjectType::TREE39;
		_UITile[1][18].SetObjectType = ObjectType::TREE40;
		_UITile[2][18].SetObjectType = ObjectType::TREE41;
		_UITile[3][18].SetObjectType = ObjectType::TREE42;
		_UITile[4][18].SetObjectType = ObjectType::NONE;
		_UITile[5][18].SetObjectType = ObjectType::NONE;
		_UITile[6][18].SetObjectType = ObjectType::NONE;
		_UITile[7][18].SetObjectType = ObjectType::NONE;
		_UITile[4][18].burglar = NULL;
		_UITile[5][18].burglar = NULL;
		_UITile[6][18].burglar = NULL;
		_UITile[7][18].burglar = NULL;
		break;
	}

}

void MapTool::ButtonInit()
{
	_button[0] = RectMakeCenter(1440, 800, 40, 40);		//UP
	_button[1] = RectMakeCenter(1440, 850, 40, 40);		//DOWN
	_button[2] = RectMakeCenter(1390, 850, 40, 40);		//LEFT
	_button[3] = RectMakeCenter(1490, 850, 40, 40);		//RIGHT
	//_button[4] = RectMakeCenter(1280, 800, 90, 40);		//Player select
	//_button[5] = RectMakeCenter(1296, 600, 48, 20);		//Enemy  select
	//_button[6] = RectMakeCenter(1440,570,50,50);		
	//_button[7] = RectMakeCenter();						//Block	 select
	//_button[8] = RectMakeCenter();						//Obejct select
}

void MapTool::ButtonControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_button[6], _ptMouse))
		{
			//_selectTile.SelectTileType = TileType::TREE;

		}
	}
}


void MapTool::CameraControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_CameraPositon.y -= 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_CameraPositon.y += 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_CameraPositon.x -= 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_CameraPositon.x += 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//UP
		if (PtInRect(&_button[0], _ptMouse))
		{
			_CameraPositon.y -= 20;
		}
		//DOWN
		if (PtInRect(&_button[1], _ptMouse))
		{
			_CameraPositon.y += 20;
		}
		//LEFT
		if (PtInRect(&_button[2], _ptMouse))
		{
			_CameraPositon.x -= 20;
		}
		//RIGHT
		if (PtInRect(&_button[3], _ptMouse))
		{
			_CameraPositon.x += 20;
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
						wallFrameSet(x, y - 1);
						break;
					case TileType::BLOCK:
						blockFrameSet(x, y);
						break;
					case TileType::OBJECT:
						objectFrameSet(x, y - 2);
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
	_selectTile.FrameX = x;
	_selectTile.FrameY = y;
	_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
	_selectTile.burglar = _UITile[x][y].burglar;
	cout << _selectTile.burglar << endl;
	/*switch (_UITile[x][y].SetBlockType)
	{
	case BlockType::NONE:
		_selectTile.FrameX = 0;
		_selectTile.FrameY = 0;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::DIRT:
		_selectTile.FrameX = 1;
		_selectTile.FrameY = 0;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::WOOD:
		_selectTile.FrameX = 2;
		_selectTile.FrameY = 0;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::STONE:
		_selectTile.FrameX = 3;
		_selectTile.FrameY = 0;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::COPPER:
		_selectTile.FrameX = 4;
		_selectTile.FrameY = 0;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::IRON:
		_selectTile.FrameX = 5;
		_selectTile.FrameY = 0;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::GOLD:
		_selectTile.FrameX = 6;
		_selectTile.FrameY = 0;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	case BlockType::PLATINUM:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectBlockType = _UITile[x][y].SetBlockType;
		break;
	}*/
}

void MapTool::wallFrameSet(int x, int y)
{
	_selectTile.SelectTileType = TileType::WALL;
	_selectTile.FrameX = x;
	_selectTile.FrameY = y;
	_selectTile.SelectWallType = _UITile[x][y+1].SetWallType;
	_selectTile.burglar = _UITile[x][y + 1].burglar;
	//switch (_UITile[x][y].SetWallType)
	//{
	//case WallType::NONE:
	//	/*	_selectTile.FrameX = x;
	//		_selectTile.FrameY = y;
	//		_selectTile.SelectWallType = _UITile[x][y].SetWallType;*/
	//	break;
	//case WallType::DIRT:
	//	_selectTile.FrameX = x;
	//	_selectTile.FrameY = y;
	//	_selectTile.SelectWallType = _UITile[x][y].SetWallType;
	//	break;
	//case WallType::WOOD:
	//	_selectTile.FrameX = x;
	//	_selectTile.FrameY = y;
	//	_selectTile.SelectWallType = _UITile[x][y].SetWallType;
	//	break;
	//case WallType::STONE:
	//	_selectTile.FrameX = x;
	//	_selectTile.FrameY = y;
	//	_selectTile.SelectWallType = _UITile[x][y].SetWallType;
	//	break;
	//}
}

void MapTool::objectFrameSet(int x, int y)
{
	_selectTile.SelectTileType = TileType::OBJECT;
	_selectTile.FrameX = x;
	_selectTile.FrameY = y;
	_selectTile.SelectObjectType = _UITile[x][y+2].SetObjectType;
	_selectTile.burglar = _UITile[x][y + 2].burglar;
	/*switch (_UITile[x][y].SetObjectType)
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
	case ObjectType::TREE:
		_selectTile.FrameX = x;
		_selectTile.FrameY = y;
		_selectTile.SelectObjectType = _UITile[x][y].SetObjectType;
	}*/
}

void MapTool::drawTile()
{
	RECT rc;
	RECT temp;

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_start.x = _ptMouse.x + _CameraPositon.x;
		_start.y = _ptMouse.y + _CameraPositon.y;
		//rc = RectMakeLTRB(_start.x, _start.y, 0, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		rc = RectMakeLTRB(_start.x, _start.y, _ptMouse.x + _CameraPositon.x, _ptMouse.y + _CameraPositon.y);

		for (int x = 0;x < MaxTile_X;x++)
		{
			for (int y = 0;y < MaxTile_Y;y++)
			{
				if (IntersectRect(&temp, &_Tile[x][y].rc, &rc))
				{
					switch (_selectTile.SelectTileType)
					{
					case TileType::PLAYER:
						break;
					case TileType::ENEMY:
						break;
					case TileType::WALL:
						_Tile[x][y].wall = _selectTile.SelectTileType;
						_Tile[x][y].wallType = _selectTile.SelectWallType;
						_Tile[x][y].FrameX2 = _selectTile.FrameX;
						_Tile[x][y].FrameY2 = _selectTile.FrameY;
						_Tile[x][y].wallBurglar = _selectTile.burglar;
						cout << _Tile[x][y].wallBurglar << endl;
						break;
					case TileType::BLOCK:
						_Tile[x][y].block = _selectTile.SelectTileType;
						_Tile[x][y].blockType = _selectTile.SelectBlockType;
						_Tile[x][y].FrameX = _selectTile.FrameX;
						_Tile[x][y].FrameY = _selectTile.FrameY;
						_Tile[x][y].blockBurglar = _selectTile.burglar;
						break;
					case TileType::OBJECT:
						_Tile[x][y].object = _selectTile.SelectTileType;
						_Tile[x][y].objectType = _selectTile.SelectObjectType;
						_Tile[x][y].FrameX3 = _selectTile.FrameX;
						_Tile[x][y].FrameY3 = _selectTile.FrameY;
						_Tile[x][y].objectBurglar = _selectTile.burglar;
						break;
					}

				}
			}
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _ptMouse.x < WINSIZEX && _ptMouse.y < WINSIZEY)
	{
		for (int x = 0;x < MaxTile_X;x++)
		{
			for (int y = 0;y < MaxTile_Y;y++)
			{
				if (PtInRect(&_Tile[x][y].rc, PointMake(_CameraPositon.x + _ptMouse.x, _CameraPositon.y + _ptMouse.y)))
				{
					switch (_selectTile.SelectTileType)
					{
					case TileType::PLAYER:
						break;
					case TileType::ENEMY:
						break;
					case TileType::WALL:
						_Tile[x][y].wall = _selectTile.SelectTileType;
						_Tile[x][y].wallType = _selectTile.SelectWallType;
						_Tile[x][y].FrameX2 = _selectTile.FrameX;
						_Tile[x][y].FrameY2 = _selectTile.FrameY;
						_Tile[x][y].wallBurglar = _selectTile.burglar;

						break;
					case TileType::BLOCK:
						_Tile[x][y].block = _selectTile.SelectTileType;
						_Tile[x][y].blockType = _selectTile.SelectBlockType;
						_Tile[x][y].FrameX = _selectTile.FrameX;
						_Tile[x][y].FrameY = _selectTile.FrameY;
						_Tile[x][y].blockBurglar = _selectTile.burglar;
						break;
					case TileType::OBJECT:
						_Tile[x][y].object = _selectTile.SelectTileType;
						_Tile[x][y].objectType = _selectTile.SelectObjectType;
						_Tile[x][y].FrameX3 = _selectTile.FrameX;
						_Tile[x][y].FrameY3 = _selectTile.FrameY;
						_Tile[x][y].objectBurglar = _selectTile.burglar;
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
	_vTile.clear();
	file = CreateFile("SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _Tile, sizeof(tagTile) * MaxTile_X * MaxTile_Y, &read, NULL);
	for (int x = 0;x < MaxTile_X;x++)
	{
		for (int y = 0;y < MaxTile_Y;y++)
		{
			_vTile.push_back(&_Tile[x][y]);
		}
	}
	CloseHandle(file);
}