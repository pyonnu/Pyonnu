#include "stdafx.h"
#include "World.h"

HRESULT World::init()
{
	_map = new Map;
	_player = new Player;
	_enemyManager = new EnemyManager;
	_ui = new UI;

	_map->init();
	_player->init();
	_enemyManager->init();
	_player->EnemyManagerLink(_enemyManager);
	_enemyManager->PlayerLink(_player);
	_ui->init();

	_player->setVTile(_map->getVTile());
	_player->setViTile(_map->getViTile());

	

	return S_OK;
}

void World::release()
{
}

void World::update()
{
	_map->setXY(_player->getStartX(),_player->getEndX(),_player->getStartY(),_player->getEndY());
	_map->update();
	_player->update();
	_enemyManager->update();
	_ui->update();
	ITEMMANAGER->update();
}

void World::render()
{
	CAMERAMANAGER->render();
	_map->render(_player->getPlayerInfo().x-WINSIZEX/2-160,_player->getPlayerInfo().y-WINSIZEY/2-90);
	_player->render();
	_enemyManager->render();
	_ui->render();
	ITEMMANAGER->render(getMemDC());
}

