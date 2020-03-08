#include "stdafx.h"
#include "DemonEye.h"

void DemonEye::Move()
{
	_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _playerPos->x, _playerPos->y);
	_enemyInfo->x += cosf(_enemyInfo->angle) * _enemyInfo->speed;
	_enemyInfo->y += -sinf(_enemyInfo->angle) *_enemyInfo->speed;
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, _enemyInfo->enemyImage->getFrameWidth(), _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Lrect = RectMake(_enemyInfo->rc.left - 3, _enemyInfo->rc.top, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Trect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.top - 3, _enemyInfo->enemyImage->getFrameWidth(), 3);
	_enemyInfo->Rrect = RectMake(_enemyInfo->rc.right, _enemyInfo->rc.top, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Brect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.bottom, _enemyInfo->enemyImage->getFrameWidth(), 3); 
}

void DemonEye::render()
{
	//Rectangle(CAMERAMANAGER->getCameraDC(),_enemyInfo->rc);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Lrect);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Trect);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Rrect);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Brect);
	_enemyInfo->enemyImage->rotateFrameRender(CAMERAMANAGER->getCameraDC(), _enemyInfo->x, _enemyInfo->y, _enemyInfo->FrameX, _enemyInfo->FrameY, _enemyInfo->angle);
}

void DemonEye::Frame()
{
	_enemyInfo->FrameCount += TIMEMANAGER->getElapsedTime();
	if (_enemyInfo->FrameCount >= 0.3f)
	{
		if (_enemyInfo->FrameY >= _enemyInfo->enemyImage->getMaxFrameY())_enemyInfo->FrameY = -1;
		_enemyInfo->FrameY++;
		_enemyInfo->FrameCount = 0;
	}
}

