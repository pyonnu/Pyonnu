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
	_ui->init();

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
	_map->render();
	_player->render();
	_enemyManager->render();
	_ui->render();
}
