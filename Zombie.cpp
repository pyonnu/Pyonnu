#include "stdafx.h"
#include "Zombie.h"

void Zombie::Move()
{
	if (_playerPos->x > _enemyInfo->x && !_enemyInfo->Right)
	{
		_enemyInfo->x += _enemyInfo->speed;
	}
	else if (_playerPos->x < _enemyInfo->x && !_enemyInfo->Left)
	{
		_enemyInfo->x -= _enemyInfo->speed;
	}
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, _enemyInfo->enemyImage->getFrameWidth(), _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Lrect = RectMake(_enemyInfo->rc.left - 3, _enemyInfo->rc.top-6, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Trect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.top, _enemyInfo->enemyImage->getFrameWidth(), 3);
	_enemyInfo->Rrect = RectMake(_enemyInfo->rc.right, _enemyInfo->rc.top-6, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Brect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.bottom+6, _enemyInfo->enemyImage->getFrameWidth(), 3);
}

void Zombie::Gravity()
{
	if (_enemyInfo->Bottom)
	{
		_enemyInfo->gravity = 0;
	}
	else
	{
		_enemyInfo->gravity -= 0.25f;
		if (_enemyInfo->gravity <= -40)_enemyInfo->gravity = -40;
	}
	_enemyInfo->y -= _enemyInfo->gravity;
}

