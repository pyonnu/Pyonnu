#include "stdafx.h"
#include "Player.h"
#include"EnemyManager.h"
HRESULT Player::init()
{
	_enemyManager = new EnemyManager;
	
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
}

void Player::render()
{
}
