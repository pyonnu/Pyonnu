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

	_ui->init();
	//_player->setTile(_map->getTile());
	_player->setVTile(_map->getVTile());
	_player->setViTile(_map->getViTile());

	//_player->setTile(_map->getTile());

	return S_OK;
}

void World::release()
{
}

void World::update()
{
	_map->update();
	_player->update();
	_enemyManager->update();
	_ui->update();
}

void World::render()
{
	CAMERAMANAGER->render();
	_map->render(_player->getPlayerInfo().x,_player->getPlayerInfo().y);
	_player->render();
	_enemyManager->render();
	_ui->render();
}
