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
	return S_OK;
}

void Map::release()
{
}

void Map::update()
{
	for (_viTile = _vTile.begin();_viTile != _vTile.end();++_viTile)
	{
		switch ((*_viTile)->blockType)
		{
		case BlockType::NONE:
			(*_viTile)->FrameX = 0;
			(*_viTile)->FrameY = 0;
			break;
		case BlockType::DIRT:
			(*_viTile)->FrameX = 1;
			(*_viTile)->FrameY = 0;
			break;
		case BlockType::WOOD:
			(*_viTile)->FrameX = 2;
			(*_viTile)->FrameY = 0;
			break;
		case BlockType::STONE:
			(*_viTile)->FrameX = 3;
			(*_viTile)->FrameY = 0;
			break;
		case BlockType::COPPER:
			(*_viTile)->FrameX = 4;
			(*_viTile)->FrameY = 0;
			break;
		case BlockType::IRON:
			(*_viTile)->FrameX = 5;
			(*_viTile)->FrameY = 0;
			break;
		case BlockType::GOLD:
			(*_viTile)->FrameX = 6;
			(*_viTile)->FrameY = 0;
			break;
		case BlockType::PLATINUM:
			(*_viTile)->FrameX = 7;
			(*_viTile)->FrameY = 0;
			break;
		}
		switch ((*_viTile)->wallType)
		{
		case WallType::NONE:
			(*_viTile)->FrameX2 = 0;
			(*_viTile)->FrameY2 = 0;
			break;
		case WallType::DIRT:
			(*_viTile)->FrameX2 = 1;
			(*_viTile)->FrameY2 = 0;
			break;
		case WallType::WOOD:
			(*_viTile)->FrameX2 = 2;
			(*_viTile)->FrameY2 = 0;
			break;
		case WallType::STONE:
			(*_viTile)->FrameX2 = 3;
			(*_viTile)->FrameY2 = 0;
			break;
		}
		switch ((*_viTile)->objectType)
		{
		case ObjectType::NONE:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::DEMONATLER:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::HEARTCRYSTAL:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::LEFTOPENDOOR:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::RIGHTOPENDOOR:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::CLOSEDOOR:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::FURNACE:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::BOX:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::WORKBENCH:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::CHIR:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::DESK:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::ANVIL:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		case ObjectType::TREE:
			(*_viTile)->FrameX3 = 0;
			(*_viTile)->FrameY3 = 0;
			break;
		}
	}
}

void Map::render()
{
	RECT temp;
	for (_viTile = _vTile.begin();_viTile != _vTile.end();++_viTile)
	{
		if (IntersectRect(&temp, &(*_viTile)->rc, &CAMERAMANAGER->getCameraRect()))
		{
			if ((*_viTile)->blockType != BlockType::NONE)
			{
				IMAGEMANAGER->findImage("BlockTiles")->frameRender(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc.left, (*_viTile)->rc.top, (*_viTile)->FrameX, (*_viTile)->FrameY);
			}
			if ((*_viTile)->objectType != ObjectType::NONE)
			{
				IMAGEMANAGER->findImage("ObjectTiles")->frameRender(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc.left, (*_viTile)->rc.top, (*_viTile)->FrameX3, (*_viTile)->FrameY3);
			}
			if (((*_viTile)->wallType != WallType::NONE && (*_viTile)->blockType == BlockType::NONE) || ((*_viTile)->wallType != WallType::NONE && (*_viTile)->objectType != ObjectType::NONE))
			{
				//IMAGEMANAGER->findImage("WallTiles")->frameRender(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc.left, (*_viTile)->rc.top, (*_viTile)->FrameX2, (*_viTile)->FrameY2);
				//Rectangle(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc);
			}
		}
	}
}

void Map::render(float x, float y)
{
	IMAGEMANAGER->findImage("Background7")->render(CAMERAMANAGER->getCameraDC(),x,y);
	RECT temp;
	
	for (_viTile = _vTile.begin();_viTile != _vTile.end();++_viTile)
	{
		
		if (IntersectRect(&temp, &(*_viTile)->rc, &CAMERAMANAGER->getCameraRect()))
		{
			if (((*_viTile)->wallType != WallType::NONE && (*_viTile)->blockType == BlockType::NONE) || ((*_viTile)->wallType != WallType::NONE && (*_viTile)->objectType != ObjectType::NONE))
			{
				IMAGEMANAGER->findImage("WallTiles")->frameRender(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc.left, (*_viTile)->rc.top, (*_viTile)->FrameX2, (*_viTile)->FrameY2);
			}
			if ((*_viTile)->blockType != BlockType::NONE)
			{
				IMAGEMANAGER->findImage("BlockTiles")->frameRender(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc.left, (*_viTile)->rc.top, (*_viTile)->FrameX, (*_viTile)->FrameY);
			}
			if ((*_viTile)->objectType != ObjectType::NONE)
			{
				IMAGEMANAGER->findImage("ObjectTiles")->frameRender(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc.left, (*_viTile)->rc.top, (*_viTile)->FrameX3, (*_viTile)->FrameY3);
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
