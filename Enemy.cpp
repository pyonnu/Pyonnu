#include "stdafx.h"
#include "Enemy.h"
HRESULT Enemy::init()
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->FrameX = 0;
	_enemyInfo->FrameY = 0;
	_enemyInfo->FrameCount = 0;
	_enemyInfo->angle = 0;
	_enemyInfo->gravity = 0;
	_enemyInfo->state = State::MOVE;

	_enemyInfo->Bottom = false;
	_enemyInfo->Left = false;
	_enemyInfo->Right = false;
	_enemyInfo->Top = false;
	_enemyInfo->delay = 0;
	_playerPos = new PlayerPos;

	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	Move();
	Frame();
	Gravity();
	_enemyInfo->idx = _enemyInfo->rc.left / TILESIZE;
	_enemyInfo->idy = _enemyInfo->rc.top / TILESIZE;

	_enemyInfo->Lid = _enemyInfo->rc.left / TILESIZE;
	_enemyInfo->Tid = _enemyInfo->rc.top / TILESIZE;
	_enemyInfo->Rid = _enemyInfo->rc.right / TILESIZE;
	_enemyInfo->Bid = _enemyInfo->rc.bottom / TILESIZE;

	if (_enemyInfo->x > _playerPos->x)
	{
		_enemyInfo->direction = Direction::LEFT;
	}
	else if (_enemyInfo->x < _playerPos->x)
	{
		_enemyInfo->direction = Direction::RIGHT;
	}


}

void Enemy::render()
{
	//Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->rc);
	/*Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Lrect);
	Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Trect);
	Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Rrect);
	Rectangle(CAMERAMANAGER->getCameraDC(), _enemyInfo->Brect);*/
	_enemyInfo->enemyImage->frameRender(CAMERAMANAGER->getCameraDC(), _enemyInfo->rc.left, _enemyInfo->rc.top, _enemyInfo->FrameX, _enemyInfo->FrameY);
}

void Enemy::Move()
{
}

void Enemy::Frame()
{
	_enemyInfo->FrameCount += TIMEMANAGER->getElapsedTime();
	if (_enemyInfo->FrameCount >= 0.3f)
	{
		if (_enemyInfo->FrameY >= _enemyInfo->enemyImage->getMaxFrameY())_enemyInfo->FrameY = -1;
		_enemyInfo->FrameY++;
		_enemyInfo->FrameCount = 0;
	}
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		_enemyInfo->FrameX = 0;
		break;
	case Direction::RIGHT:
		_enemyInfo->FrameX = 1;
		break;
	}

}

void Enemy::Gravity()
{
}

void Enemy::EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, image* enemyImage, Type type)
{
	this->init();
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->speed = speed;
	_enemyInfo->damage = damage;
	_enemyInfo->HP = HP;
	_enemyInfo->Defense = Defense;
	_enemyInfo->enemyImage = enemyImage;
	_enemyInfo->type = type;
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, _enemyInfo->enemyImage->getFrameWidth(), _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Lrect = RectMake(_enemyInfo->rc.left - 3, _enemyInfo->rc.top, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Trect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.top - 3, _enemyInfo->enemyImage->getFrameWidth(), 3);
	_enemyInfo->Rrect = RectMake(_enemyInfo->rc.right, _enemyInfo->rc.top, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Brect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.bottom, _enemyInfo->enemyImage->getFrameWidth(), 3);
}

void Enemy::EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, string enemyImage, Type type)
{
	this->init();
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->speed = speed;
	_enemyInfo->damage = damage;
	_enemyInfo->HP = HP;
	_enemyInfo->Defense = Defense;
	_enemyInfo->enemyImage = IMAGEMANAGER->findImage(enemyImage);
	_enemyInfo->type = type;
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, _enemyInfo->enemyImage->getFrameWidth(), _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Lrect = RectMake(_enemyInfo->rc.left - 3, _enemyInfo->rc.top, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Trect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.top - 3, _enemyInfo->enemyImage->getFrameWidth(), 3);
	_enemyInfo->Rrect = RectMake(_enemyInfo->rc.right, _enemyInfo->rc.top, 3, _enemyInfo->enemyImage->getFrameHeight());
	_enemyInfo->Brect = RectMake(_enemyInfo->rc.left, _enemyInfo->rc.bottom, _enemyInfo->enemyImage->getFrameWidth(), 3);
}

void Enemy::Hit(bool hit, float damage)
{
	if (_enemyInfo->delay == 0)
	{
		if (_enemyInfo->Defense / 2 - damage < 1)_enemyInfo->HP - 1;
		else _enemyInfo->HP -= damage;
		if (_enemyInfo->x < _playerPos->x)
		{
			_enemyInfo->y -= 15;
			_enemyInfo->x -= 50;
			cout << "왼족으로 날아간드아ㅏㅏㅏㅏㅏㅏㅏ" << endl;
		}
		else if (_enemyInfo->x > _playerPos->x)
		{
			_enemyInfo->y -= 15;
			_enemyInfo->x += 50;
			cout << "오른족으로 날아간드아ㅏㅏㅏㅏㅏㅏㅏ" << endl;
		}
	}
	
	_enemyInfo->delay += TIMEMANAGER->getElapsedTime();
	if (_enemyInfo->delay >= 5)
	{
		_enemyInfo->delay = 0;
	}
	cout << _enemyInfo->delay << endl;
}
