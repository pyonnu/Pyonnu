#include "stdafx.h"
#include "Slime.h"

void Slime::Move()
{
	delay += TIMEMANAGER->getElapsedTime();
	if (delay >= 2)
	{
		if (_enemyInfo->x < _playerPos->x)
		{
			_enemyInfo->y -= 10;
			_enemyInfo->x += 5;
		}
		else
		{
			_enemyInfo->y -= 10;
			_enemyInfo->x -= 5;
		}
		delay = 0;
	}
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, _enemyInfo->enemyImage->getFrameWidth(), _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Lrect = RectMake(_enemyInfo->rc.left - 3, _enemyInfo->rc.top - 6, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Trect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.top, _enemyInfo->enemyImage->getFrameWidth(), 3);
	_enemyInfo->Rrect = RectMake(_enemyInfo->rc.right, _enemyInfo->rc.top - 6, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Brect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.bottom + 6, _enemyInfo->enemyImage->getFrameWidth(), 3);
}

void Slime::Frame()
{
	_enemyInfo->FrameCount += TIMEMANAGER->getElapsedTime();
	if (_enemyInfo->FrameCount >= 0.3f)
	{
		if (_enemyInfo->FrameY >= _enemyInfo->enemyImage->getMaxFrameY())_enemyInfo->FrameY = -1;
		_enemyInfo->FrameY++;
		_enemyInfo->FrameCount = 0;
	}
}

void Slime::Gravity()
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
