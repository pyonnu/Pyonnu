#include "stdafx.h"
#include "EyeOfCthulhu.h"

void EyeOfCthulhu::EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, image* enemyImage)
{
	_enemyInfo = new EnemyInfo;
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	this->init();
	_enemyInfo->state = State::MOVE;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->y = speed;
	_enemyInfo->damage = damage;
	_enemyInfo->HP = HP;
	_enemyInfo->Defense = Defense;
	_enemyInfo->enemyImage = enemyImage;
	phase = Phase::PHASE1;
}

void EyeOfCthulhu::EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, string enemyImage)
{
	_enemyInfo = new EnemyInfo;
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	this->init();
	_enemyInfo->state = State::MOVE;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->y = speed;
	_enemyInfo->damage = damage;
	_enemyInfo->HP = HP;
	_enemyInfo->Defense = Defense;
	_enemyInfo->enemyImage = IMAGEMANAGER->findImage(enemyImage);
	phase = Phase::PHASE1;
}

void EyeOfCthulhu::Move()
{
}

void EyeOfCthulhu::Frame()
{
}
