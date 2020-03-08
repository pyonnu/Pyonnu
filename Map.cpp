#include "stdafx.h"
#include "Map.h"

HRESULT Map::init()
{
	setMap();
	POINT size;
	size.x = MaxTile_X * TILESIZE;
	size.y = MaxTile_Y * TILESIZE;
	CAMERAMANAGER->setCameraSize(size);
	CAMERAMANAGER->changeCameraType();
	_startX = _startY = _endX = _endY = 0;
	return S_OK;
}

void Map::release()
{
}

void Map::update()
{
	for (int x = _startX;x < _endX;++x)
	{
		for (int y = _startY;y < _endY;++y)
		{
			//타일 타입이 none이 아닐때만
			if (_vTile[MaxTile_Y * x + y]->currentTileBlockType != TileType::NONE)
			{
				if (_vTile[MaxTile_Y * x + y]->blockBurglar<=0 )
				{
					BlockItemSpawn(x,y);
					_vTile[MaxTile_Y * x + y]->block = TileType::NONE;
					_vTile[MaxTile_Y * x + y]->blockType = BlockType::NONE;
				}
				
			}
			if (_vTile[MaxTile_Y * x + y]->currentTileWallType != TileType::NONE)
			{
				if (_vTile[MaxTile_Y * x + y]->wallBurglar <= 0)
				{
					WallItemSpawn(x, y);
					_vTile[MaxTile_Y * x + y]->wall = TileType::NONE;
					_vTile[MaxTile_Y * x + y]->wallType = WallType::NONE;
				}
			}
			if (_vTile[MaxTile_Y * x + y]->currentTileObjectType != TileType::NONE)
			{
				if (_vTile[MaxTile_Y * x + y]->objectBurglar <= 0)
				{
					ObjectTileUpdate(x, y);
				}
			}
			if (_vTile[MaxTile_Y * x + y]->objectType == ObjectType::WORKBENCH2)
			{
				_vTile[MaxTile_Y * (x - 1) + y]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x - 2) + y]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x - 3) + y]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x - 4) + y]->WORKBENCH = true;

				_vTile[MaxTile_Y * (x + 1) + y]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x + 2) + y]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x + 3) + y]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x + 4) + y]->WORKBENCH = true;

				_vTile[MaxTile_Y * (x - 1) + y-1]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x - 2) + y-1]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x - 3) + y-1]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x - 4) + y-1]->WORKBENCH = true;

				_vTile[MaxTile_Y * (x + 1) + y-1]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x + 2) + y-1]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x + 3) + y-1]->WORKBENCH = true;
				_vTile[MaxTile_Y * (x + 4) + y-1]->WORKBENCH = true;
			}
			if (_vTile[MaxTile_Y * x + y]->objectType == ObjectType::ANVIL2)
			{
				_vTile[MaxTile_Y *( x - 1)+ y]->ANVIL = true;
				_vTile[MaxTile_Y *( x - 2)+ y]->ANVIL = true;
				_vTile[MaxTile_Y *( x - 3)+ y]->ANVIL = true;
				_vTile[MaxTile_Y *( x - 4)+ y]->ANVIL = true;

				_vTile[MaxTile_Y *(x + 1)+ y]->ANVIL = true;
				_vTile[MaxTile_Y *(x + 2)+ y]->ANVIL = true;
				_vTile[MaxTile_Y *(x + 3)+ y]->ANVIL = true;
				_vTile[MaxTile_Y *(x + 4)+ y]->ANVIL = true;

				_vTile[MaxTile_Y * (x - 1) + y - 1]->ANVIL= true;
				_vTile[MaxTile_Y * (x - 2) + y - 1]->ANVIL= true;
				_vTile[MaxTile_Y * (x - 3) + y - 1]->ANVIL= true;
				_vTile[MaxTile_Y * (x - 4) + y - 1]->ANVIL= true;

				_vTile[MaxTile_Y * (x + 1) + y - 1]->ANVIL = true;
				_vTile[MaxTile_Y * (x + 2) + y - 1]->ANVIL = true;
				_vTile[MaxTile_Y * (x + 3) + y - 1]->ANVIL = true;
				_vTile[MaxTile_Y * (x + 4) + y - 1]->ANVIL = true;
			}
			if (_vTile[MaxTile_Y * x + y]->objectType == ObjectType::FURNACE4)
			{
				_vTile[MaxTile_Y * (x - 1) + y]->FURNACE = true;
				_vTile[MaxTile_Y * (x - 2) + y]->FURNACE = true;
				_vTile[MaxTile_Y * (x - 3) + y]->FURNACE = true;
				_vTile[MaxTile_Y * (x - 4) + y]->FURNACE = true;

				_vTile[MaxTile_Y * (x + 1) + y]->FURNACE = true;
				_vTile[MaxTile_Y * (x + 2) + y]->FURNACE = true;
				_vTile[MaxTile_Y * (x + 3) + y]->FURNACE = true;
				_vTile[MaxTile_Y * (x + 4) + y]->FURNACE = true;

				_vTile[MaxTile_Y * (x - 1) + y - 1]->FURNACE= true;
				_vTile[MaxTile_Y * (x - 2) + y - 1]->FURNACE= true;
				_vTile[MaxTile_Y * (x - 3) + y - 1]->FURNACE= true;
				_vTile[MaxTile_Y * (x - 4) + y - 1]->FURNACE= true;

				_vTile[MaxTile_Y * (x + 1) + y - 1]->FURNACE = true;
				_vTile[MaxTile_Y * (x + 2) + y - 1]->FURNACE = true;
				_vTile[MaxTile_Y * (x + 3) + y - 1]->FURNACE = true;
				_vTile[MaxTile_Y * (x + 4) + y - 1]->FURNACE = true;
			}
			if (_vTile[MaxTile_Y * x + y]->objectType == ObjectType::DEMONALTER4)
			{
				_vTile[MaxTile_Y * (x - 1) + y]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x - 2) + y]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x - 3) + y]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x - 4) + y]->DEMONALTER = true;

				_vTile[MaxTile_Y * (x + 1) + y]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x + 2) + y]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x + 3) + y]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x + 4) + y]->DEMONALTER = true;

				_vTile[MaxTile_Y * (x - 1) + y - 1]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x - 2) + y - 1]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x - 3) + y - 1]->DEMONALTER = true;
				_vTile[MaxTile_Y * (x - 4) + y - 1]->DEMONALTER = true;

				_vTile[MaxTile_Y * (x + 1) + y - 1]->DEMONALTER = true;
				_vTile[MaxTile_Y *(x + 2) + y - 1]->DEMONALTER = true;
				_vTile[MaxTile_Y *(x + 3) + y - 1]->DEMONALTER = true;
				_vTile[MaxTile_Y *(x + 4) + y - 1]->DEMONALTER = true;
			}
			_vTile[MaxTile_Y * x + y]->currentTileBlockType = _vTile[MaxTile_Y * x + y]->block;
			_vTile[MaxTile_Y * x + y]->currentTileWallType = _vTile[MaxTile_Y * x + y]->wall;
			_vTile[MaxTile_Y * x + y]->currentTileObjectType = _vTile[MaxTile_Y * x + y]->object;
			_vTile[MaxTile_Y * x + y]->currentBlockType = _vTile[MaxTile_Y * x + y]->blockType;
			_vTile[MaxTile_Y * x + y]->currentWallType = _vTile[MaxTile_Y * x + y]->wallType;
			_vTile[MaxTile_Y * x + y]->currentObjectType = _vTile[MaxTile_Y * x + y]->objectType;
			TileUpdate(x, y);
		}
	}
	
		
	
}

void Map::render()
{
}

void Map::render(float x, float y)
{
	IMAGEMANAGER->findImage("Background7")->render(CAMERAMANAGER->getCameraDC(), x, y);
	RECT temp;
	
	for (int x = _startX;x < _endX;++x)
	{
		for (int y = _startY;y < _endY;++y)
		{
			if ((_vTile[MaxTile_Y * x + y]->wallType != WallType::NONE && _vTile[MaxTile_Y * x + y]->blockType == BlockType::NONE) || (_vTile[MaxTile_Y * x + y]->wallType != WallType::NONE && _vTile[MaxTile_Y * x + y]->objectType != ObjectType::NONE))
			{
				IMAGEMANAGER->findImage("WallTiles")->frameRender(CAMERAMANAGER->getCameraDC(), _vTile[MaxTile_Y * x + y]->rc.left, _vTile[MaxTile_Y * x + y]->rc.top, _vTile[MaxTile_Y * x + y]->FrameX2, _vTile[MaxTile_Y * x + y]->FrameY2);
			}
			if (_vTile[MaxTile_Y * x + y]->blockType != BlockType::NONE)
			{
				IMAGEMANAGER->findImage("BlockTiles")->frameRender(CAMERAMANAGER->getCameraDC(), _vTile[MaxTile_Y * x + y]->rc.left, _vTile[MaxTile_Y * x + y]->rc.top, _vTile[MaxTile_Y * x + y]->FrameX, _vTile[MaxTile_Y * x + y]->FrameY);
			}
			if (_vTile[MaxTile_Y * x + y]->objectType != ObjectType::NONE)
			{
				IMAGEMANAGER->findImage("ObjectTiles")->frameRender(CAMERAMANAGER->getCameraDC(), _vTile[MaxTile_Y * x + y]->rc.left, _vTile[MaxTile_Y * x + y]->rc.top, _vTile[MaxTile_Y * x + y]->FrameX3, _vTile[MaxTile_Y * x + y]->FrameY3);
			}
		}
	}
}

void Map::setMap()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다
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

void Map::TileUpdate(int x, int y)
{
	switch (_vTile[MaxTile_Y * x + y]->blockType)
	{
	case BlockType::NONE:
		_vTile[MaxTile_Y * x + y]->FrameX = 0;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	case BlockType::DIRT:
		_vTile[MaxTile_Y * x + y]->FrameX = 1;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	case BlockType::WOOD:
		_vTile[MaxTile_Y * x + y]->FrameX = 7;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	case BlockType::STONE:
		_vTile[MaxTile_Y * x + y]->FrameX = 2;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	case BlockType::COPPER:
		_vTile[MaxTile_Y * x + y]->FrameX = 3;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	case BlockType::IRON:
		_vTile[MaxTile_Y * x + y]->FrameX = 4;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	case BlockType::GOLD:
		_vTile[MaxTile_Y * x + y]->FrameX = 5;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	case BlockType::PLATINUM:
		_vTile[MaxTile_Y * x + y]->FrameX = 6;
		_vTile[MaxTile_Y * x + y]->FrameY = 0;
		break;
	}
	switch (_vTile[MaxTile_Y * x + y]->wallType)
	{
	case WallType::NONE:
		_vTile[MaxTile_Y * x + y]->FrameX2 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY2 = 0;
		break;
	case WallType::DIRT:
		_vTile[MaxTile_Y * x + y]->FrameX2 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY2 = 0;
		break;
	case WallType::WOOD:
		_vTile[MaxTile_Y * x + y]->FrameX2 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY2 = 0;
		break;
	case WallType::STONE:
		_vTile[MaxTile_Y * x + y]->FrameX2 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY2 = 0;
		break;
	}
	switch (_vTile[MaxTile_Y * x + y]->objectType)
	{
	case ObjectType::NONE:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 7;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 16;
		break;
	case ObjectType::DESK1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 0;
		break;
	case ObjectType::DESK2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 0;
		break;
	case ObjectType::DESK3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 0;
		break;
	case ObjectType::DESK4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 1;
		break;
	case ObjectType::DESK5:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 1;
		break;
	case ObjectType::DESK6:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 1;
		break;
	case ObjectType::HEARTCRYSTAL1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 0;
		break;
	case ObjectType::HEARTCRYSTAL2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 0;
		break;
	case ObjectType::HEARTCRYSTAL3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 1;
		break;
	case ObjectType::HEARTCRYSTAL4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 1;
		break;
	case ObjectType::LEFTCHIR1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 0;
		break;
	case ObjectType::LEFTCHIR2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 1;
		break;
	case ObjectType::RIGHTCHIR1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 6;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 0;
		break;
	case ObjectType::RIGHTCHIR2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 6;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 1;
		break;
	case ObjectType::FURNACE1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 2;
		break;
	case ObjectType::FURNACE2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 2;
		break;
	case ObjectType::FURNACE3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 2;
		break;
	case ObjectType::FURNACE4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 3;
		break;
	case ObjectType::FURNACE5:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 3;
		break;
	case ObjectType::FURNACE6:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 3;
		break;
	case ObjectType::BOX1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 2;
		break;
	case ObjectType::BOX2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 2;
		break;
	case ObjectType::BOX3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 3;
		break;
	case ObjectType::BOX4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 3;
		break;
	case ObjectType::WORKBENCH1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 2;
		break;
	case ObjectType::WORKBENCH2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 6;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 2;
		break;
	case ObjectType::ANVIL1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 3;
		break;
	case ObjectType::ANVIL2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 6;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 3;
		break;
	case ObjectType::RIGHT_OPENDOOR1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 4;
		break;
	case ObjectType::RIGHT_OPENDOOR2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 4;
		break;
	case ObjectType::RIGHT_OPENDOOR3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 5;
		break;
	case ObjectType::RIGHT_OPENDOOR4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 5;
		break;
	case ObjectType::RIGHT_OPENDOOR5:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 6;
		break;
	case ObjectType::RIGHT_OPENDOOR6:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 6;
		break;
	case ObjectType::LEFT_OPENDOOR1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 7;
		break;
	case ObjectType::LEFT_OPENDOOR2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 6;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 7;
		break;
	case ObjectType::LEFT_OPENDOOR3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 8;
		break;
	case ObjectType::LEFT_OPENDOOR4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 6;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 8;
		break;
	case ObjectType::LEFT_OPENDOOR5:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 9;
		break;
	case ObjectType::LEFT_OPENDOOR6:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 6;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 9;
		break;
	case ObjectType::CLOSEDOOR1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 4;
		break;
	case ObjectType::CLOSEDOOR2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 5;
		break;
	case ObjectType::CLOSEDOOR3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 6;
		break;
	case ObjectType::DEMONALTER1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 4;
		break;
	case ObjectType::DEMONALTER2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 4;
		break;
	case ObjectType::DEMONALTER3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 4;
		break;
	case ObjectType::DEMONALTER4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 5;
		break;
	case ObjectType::DEMONALTER5:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 5;
		break;
	case ObjectType::DEMONALTER6:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 5;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 5;
		break;
	case ObjectType::TREE1:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 7;
		break;
	case ObjectType::TREE2:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 7;
		break;
	case ObjectType::TREE3:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 7;
		break;
	case ObjectType::TREE4:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 7;
		break;
	case ObjectType::TREE5:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 7;
		break;
	case ObjectType::TREE6:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 8;
		break;
	case ObjectType::TREE7:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 8;
		break;
	case ObjectType::TREE8:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 8;
		break;
	case ObjectType::TREE9:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 8;
		break;
	case ObjectType::TREE10:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 8;
		break;
	case ObjectType::TREE11:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 9;
		break;
	case ObjectType::TREE12:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 9;
		break;
	case ObjectType::TREE13:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 9;
		break;
	case ObjectType::TREE14:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 9;
		break;
	case ObjectType::TREE15:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 9;
		break;
	case ObjectType::TREE16:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 10;
		break;
	case ObjectType::TREE17:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 10;
		break;
	case ObjectType::TREE18:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 10;
		break;
	case ObjectType::TREE19:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 10;
		break;
	case ObjectType::TREE20:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 10;
		break;
	case ObjectType::TREE21:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 11;
		break;
	case ObjectType::TREE22:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 11;
		break;
	case ObjectType::TREE23:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 11;
		break;
	case ObjectType::TREE24:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 11;
		break;
	case ObjectType::TREE25:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 11;
		break;
	case ObjectType::TREE26:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 12;
		break;
	case ObjectType::TREE27:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 12;
		break;
	case ObjectType::TREE28:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 13;
		break;
	case ObjectType::TREE29:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 13;
		break;
	case ObjectType::TREE30:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 13;
		break;
	case ObjectType::TREE31:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 13;
		break;
	case ObjectType::TREE32:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 13;
		break;
	case ObjectType::TREE33:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 14;
		break;
	case ObjectType::TREE34:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 14;
		break;
	case ObjectType::TREE35:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 14;
		break;
	case ObjectType::TREE36:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 4;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 14;
		break;
	case ObjectType::TREE37:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 15;
		break;
	case ObjectType::TREE38:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 15;
		break;
	case ObjectType::TREE39:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 0;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 16;
		break;
	case ObjectType::TREE40:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 1;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 16;
		break;
	case ObjectType::TREE41:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 2;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 16;
		break;
	case ObjectType::TREE42:
		_vTile[MaxTile_Y * x + y]->FrameX3 = 3;
		_vTile[MaxTile_Y * x + y]->FrameY3 = 16;
		break;
	}
}

void Map::BlockItemSpawn(int x, int y)
{
	switch (_vTile[MaxTile_Y * x + y]->currentBlockType)
	{
	case BlockType::DIRT:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE,type::DIRT_BLOCK,ItemType::BLOCK,ItemType::METERIAL, IMAGEMANAGER->findImage("Item_1"),1);
		break;
	case BlockType::WOOD:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE,type::WOOD, ItemType::BLOCK, ItemType::METERIAL,IMAGEMANAGER->findImage("Item_3"),1);
		break;
	case BlockType::STONE:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE,type::STONE_BLOCK, ItemType::BLOCK,ItemType::METERIAL, IMAGEMANAGER->findImage("Item_2"), 1);
		break;
	case BlockType::COPPER:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::COPPER, ItemType::BLOCK, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_4"), 1);
		break;
	case BlockType::IRON:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::IRON, ItemType::BLOCK, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_5"), 1);
		break;
	case BlockType::GOLD:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::GOLD, ItemType::BLOCK, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_6"), 1);
		break;
	case BlockType::PLATINUM:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::PLATINUM, ItemType::BLOCK, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_7"), 1);
		break;
	}
}

void Map::WallItemSpawn(int x, int y)
{
	switch (_vTile[MaxTile_Y * x + y]->currentWallType)
	{
	case WallType::DIRT:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::DIRT_WALL, ItemType::WALL, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_68"), 1);
		break;
	case WallType::WOOD:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::WOOD_WALL, ItemType::WALL, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_60"), 1);
		break;
	case WallType::STONE:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::STONE_WALL, ItemType::WALL, ItemType::METERIAL, IMAGEMANAGER->findImage("Item_69"), 1);
		break;
	}
}

void Map::ObjectTileUpdate(int x, int y)
{
	if(_vTile[MaxTile_Y * x + y]->objectBurglar <= 0)
	switch (_vTile[MaxTile_Y * x + y]->objectType)
	{
	case ObjectType::DESK1:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+2) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+2) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1) + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1) + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y *(x+2) + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y *(x+2) + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y+1]->objectBurglar = 0;
		break;
	case ObjectType::DESK2:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;;
		_vTile[MaxTile_Y * (x) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x +1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x +1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y + 1]-> object = TileType::NONE;
		_vTile[MaxTile_Y * (x) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y+1]->objectBurglar = 0;
		break;
	case ObjectType::DESK3:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x -2) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x- 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x- 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x -2) + y+1]->objectBurglar = 0;
		break;
	case ObjectType::DESK4:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x) + y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+2)+y-1]->objectBurglar = 0;
		break;
	case ObjectType::DESK5:
		_vTile[MaxTile_Y * x + y]->objectType= ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x -1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x -1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-1]->objectBurglar = 0;
		break;
	case ObjectType::DESK6:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::HEARTCRYSTAL1:
		_vTile[MaxTile_Y * (x) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x) + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x) + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1) + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1) + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::HEARTCRYSTAL2:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::HEARTCRYSTAL3:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::HEARTCRYSTAL4:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::LEFTCHIR1:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::LEFTCHIR2:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::RIGHTCHIR1:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::RIGHTCHIR2:
		_vTile[MaxTile_Y * x + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * x + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * x + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * x + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::FURNACE1:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+2)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+2)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+2)+y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+2)+y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::FURNACE2:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::FURNACE3:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::FURNACE4:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::FURNACE5:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::FURNACE6:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 2) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 2) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::BOX1:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y+1]->objectBurglar = 0;
		break;
	case ObjectType::BOX2:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y + 1]->objectBurglar = 0;
		break;
	case ObjectType::BOX3:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::BOX4:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y - 1]->objectBurglar = 0;
		break;
	case ObjectType::WORKBENCH1:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->objectBurglar = 0;
		break;
	case ObjectType::WORKBENCH2:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;
		break;
	case ObjectType::ANVIL1:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;
		break;
	case ObjectType::ANVIL2:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x - 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x - 1) + y]->objectBurglar = 0;
		break;
	case ObjectType::RIGHT_OPENDOOR1:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x ) + y + 2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x ) + y + 2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x ) + y + 2]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y + 2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 2]->objectBurglar = 0;
		break;
	case ObjectType::LEFT_OPENDOOR1:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x) + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x) + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y + 1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y + 1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y + 1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x ) + y + 2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x ) + y + 2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x ) + y + 2]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 1) + y + 2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 1) + y + 2]->objectBurglar = 0;
		break;
	case ObjectType::CLOSEDOOR1:
		_vTile[MaxTile_Y * (x)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x ) + y+1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x ) + y+1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x ) + y+1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x ) + y+2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x ) + y+2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x ) + y+2]->objectBurglar = 0;
		break;
	case ObjectType::TREE41:
		_vTile[MaxTile_Y * (x) + y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x) + y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x) + y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y-1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y-1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y-1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y-1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y-1]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-1]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-1]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y-2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y-2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-2]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y-2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-2]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y-2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-2]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y-2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-2]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y-3]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y-3]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-3]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y-3]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-3]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-3]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y-3]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-3]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-3]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y-3]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-3]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-3]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y-4]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y-4]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-4]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y-4]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-4]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-4]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y-4]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-4]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-4]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y-4]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-4]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-4]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y-5]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y-5]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-5]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y-5]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-5]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y-5]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y-5]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-5]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y-5]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y-5]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-5]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y-5]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y-6]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y-6]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y-6]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y - 6]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 6]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 6]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y - 6]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 6]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 6]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y - 6]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 6]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 6]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 7]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 7]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 7]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y - 7]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 7]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 7]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y - 7]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 7]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 7]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y - 7]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 7]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 7]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 8]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 8]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 8]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y - 8]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 8]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 8]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y - 8]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 8]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 8]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y - 8]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 8]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 8]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 9]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 9]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 9]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y - 9]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 9]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 9]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y - 9]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 9]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 9]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x+1)+y - 9]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 9]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x+1)+y - 9]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x)+y - 10]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x)+y - 10]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x)+y - 10]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-1)+y - 10]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 10]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-1)+y - 10]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-2)+y - 10]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 10]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-2)+y - 10]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x-3)+y - 10]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x-3)+y - 10]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x-3)+y - 10]->objectBurglar = 0;


		_vTile[MaxTile_Y * (x + 2) + y - 2]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 2]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 2]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 3]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 3]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 3]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 4]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 4]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 4]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 5]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 5]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 5]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 6]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 6]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 6]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 7]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 7]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 7]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 8]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 8]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 8]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 9]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 9]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 9]->objectBurglar = 0;

		_vTile[MaxTile_Y * (x + 2) + y - 10]->objectType = ObjectType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 10]->object = TileType::NONE;
		_vTile[MaxTile_Y * (x + 2) + y - 10]->objectBurglar = 0;

		break;
	default:
		break;
		
	}
	ObjectItemSpawn(x, y);
}

void Map::ObjectItemSpawn(int x, int y)
{
	switch (_vTile[MaxTile_Y * x + y]->currentObjectType)
	{
	case ObjectType::DESK1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::DESK, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_53"), 1);
		break;
	case ObjectType::DESK2:
		break;
	case ObjectType::DESK3:
		break;
	case ObjectType::DESK4:
		break;
	case ObjectType::DESK5:
		break;
	case ObjectType::DESK6:
		break;
	case ObjectType::HEARTCRYSTAL1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::HEARTCRYSTAL, ItemType::CONSUMBLE, IMAGEMANAGER->findImage("Item_67"), 1);
		break;
	case ObjectType::HEARTCRYSTAL2:
		break;
	case ObjectType::HEARTCRYSTAL3:
		break;
	case ObjectType::HEARTCRYSTAL4:
		break;
	case ObjectType::LEFTCHIR1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::CHIR, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_57"), 1);
		break;
	case ObjectType::LEFTCHIR2:
		break;
	case ObjectType::RIGHTCHIR1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::CHIR, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_57"), 1);
		break;
	case ObjectType::RIGHTCHIR2:
		break;
	case ObjectType::FURNACE1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::FURNACE, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_54"), 1);
		break;
	case ObjectType::FURNACE2:
		break;
	case ObjectType::FURNACE3:
		break;
	case ObjectType::FURNACE4:
		break;
	case ObjectType::FURNACE5:
		break;
	case ObjectType::FURNACE6:
		break;
	case ObjectType::BOX1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::BOX, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_58"), 1);
		break;
	case ObjectType::BOX2:
		break;
	case ObjectType::BOX3:
		break;
	case ObjectType::BOX4:
		break;
	case ObjectType::WORKBENCH1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::WORKBENCH, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_55"), 1);
		break;
	case ObjectType::WORKBENCH2:
		break;
	case ObjectType::ANVIL1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::ANVIL, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_56"), 1);
		break;
	case ObjectType::ANVIL2:
		break;
	case ObjectType::RIGHT_OPENDOOR1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::DOOR, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_59"), 1);
		break;
	case ObjectType::RIGHT_OPENDOOR2:
		break;
	case ObjectType::RIGHT_OPENDOOR3:
		break;
	case ObjectType::RIGHT_OPENDOOR4:
		break;
	case ObjectType::RIGHT_OPENDOOR5:
		break;
	case ObjectType::RIGHT_OPENDOOR6:
		break;
	case ObjectType::LEFT_OPENDOOR1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::DOOR, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_59"), 1);
		break;
	case ObjectType::LEFT_OPENDOOR2:
		break;
	case ObjectType::LEFT_OPENDOOR3:
		break;
	case ObjectType::LEFT_OPENDOOR4:
		break;
	case ObjectType::LEFT_OPENDOOR5:
		break;
	case ObjectType::LEFT_OPENDOOR6:
		break;
	case ObjectType::CLOSEDOOR1:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::DOOR, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_59"), 1);
		break;
	case ObjectType::CLOSEDOOR2:
		break;
	case ObjectType::CLOSEDOOR3:
		break;
	case ObjectType::DEMONALTER1:
		break;
	case ObjectType::DEMONALTER2:
		break;
	case ObjectType::DEMONALTER3:
		break;
	case ObjectType::DEMONALTER4:
		break;
	case ObjectType::DEMONALTER5:
		break;
	case ObjectType::DEMONALTER6:
		break;
	case ObjectType::TREE1:
		break;
	case ObjectType::TREE2:
		break;
	case ObjectType::TREE3:
		break;
	case ObjectType::TREE4:
		break;
	case ObjectType::TREE5:
		break;
	case ObjectType::TREE6:
		break;
	case ObjectType::TREE7:
		break;
	case ObjectType::TREE8:
		break;
	case ObjectType::TREE9:
		break;
	case ObjectType::TREE10:
		break;
	case ObjectType::TREE11:
		break;
	case ObjectType::TREE12:
		break;
	case ObjectType::TREE13:
		break;
	case ObjectType::TREE14:
		break;
	case ObjectType::TREE15:
		break;
	case ObjectType::TREE16:
		break;
	case ObjectType::TREE17:
		break;
	case ObjectType::TREE18:
		break;
	case ObjectType::TREE19:
		break;
	case ObjectType::TREE20:
		break;
	case ObjectType::TREE21:
		break;
	case ObjectType::TREE22:
		break;
	case ObjectType::TREE23:
		break;
	case ObjectType::TREE24:
		break;
	case ObjectType::TREE25:
		break;
	case ObjectType::TREE26:
		break;
	case ObjectType::TREE27:
		break;
	case ObjectType::TREE28:
		break;
	case ObjectType::TREE29:
		break;
	case ObjectType::TREE30:
		break;
	case ObjectType::TREE31:
		break;
	case ObjectType::TREE32:
		break;
	case ObjectType::TREE33:
		break;
	case ObjectType::TREE34:
		break;
	case ObjectType::TREE35:
		break;
	case ObjectType::TREE36:
		break;
	case ObjectType::TREE37:
		break;
	case ObjectType::TREE38:
		break;
	case ObjectType::TREE39:
		break;
	case ObjectType::TREE40:
		break;
	case ObjectType::TREE41:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::WOOD, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_3"), 10);
		break;
	case ObjectType::TREE42:
		ITEMMANAGER->CreateItem(x * TILESIZE, y * TILESIZE, type::WOOD, ItemType::BLOCK, IMAGEMANAGER->findImage("Item_3"), 10);
		break;
	}
}
