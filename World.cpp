#include "stdafx.h"
#include "World.h"

HRESULT World::init()
{
	_player = new Player;
	_enemyManager = new EnemyManager;
	_item = new Item;

	_player->init();
	_item->init();
	_enemyManager->init();
	return S_OK;
}

void World::release()
{
}

void World::update()
{
	_player->update();
	_item->update();
	_enemyManager->update();
}

void World::render()
{
	_player->render();
	_item->render();
	_enemyManager->update();
}
