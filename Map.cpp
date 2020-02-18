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
	
}

void Map::render()
{
	RECT temp;
	for (_viTile = _vTile.begin();_viTile != _vTile.end();++_viTile)
	{
		if (IntersectRect(&temp, &(*_viTile)->rc, &CAMERAMANAGER->getCameraRect()))
		{
			if (((*_viTile)->wallType != WallType::NONE && (*_viTile)->blockType == BlockType::NONE)||((*_viTile)->wallType != WallType::NONE && (*_viTile)->objectType != ObjectType::NONE))
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

void Map::render(float x, float y)
{
	IMAGEMANAGER->findImage("Background6")->render(CAMERAMANAGER->getCameraDC(), x, y);
	RECT temp;
	
	for (_viTile = _vTile.begin();_viTile != _vTile.end();++_viTile)
	{
		
		if (IntersectRect(&temp, &(*_viTile)->rc, &CAMERAMANAGER->getCameraRect()))
		{
			Rectangle(CAMERAMANAGER->getCameraDC(), (*_viTile)->rc);
			if (((*_viTile)->wallType != WallType::NONE && (*_viTile)->blockType == BlockType::NONE) || ((*_viTile)->wallType != WallType::NONE && (*_viTile)->objectType == ObjectType::NONE))
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
			_mTile.insert(make_pair(&_Tile[x][y].index, &_Tile[x][y]));
		}
	}
	CloseHandle(file);
}
