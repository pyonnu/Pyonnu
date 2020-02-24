#include "stdafx.h"
#include "Player.h"
#include"EnemyManager.h"
HRESULT Player::init()
{
	_jump = new Jump;
	_move = new Move;
	_attack = new Attack;

	//_jump->init(&_playerInfo.y);
	_move->init();
	_attack->init();

	_enemyManager = new EnemyManager;

	_playerInfo.direction = PlayerDirection::RIGHT;

	_playerInfo.FrameCount = 0;
	_playerInfo.FrameX = 0;
	_playerInfo.HeadFrameY = 0;
	_playerInfo.BodyFrameY = 0;
	_playerInfo.LegsFrameY = 0;

	_playerInfo.x = WINSIZEX / 2 + TILESIZE;
	_playerInfo.y = 1400;
	_playerInfo.rect = RectMake(_playerInfo.x, _playerInfo.y, 60, 96);

	_playerInfo.Head = IMAGEMANAGER->findImage("Player_Head");
	_playerInfo.Body = IMAGEMANAGER->findImage("Player_Body");
	_playerInfo.Legs = IMAGEMANAGER->findImage("Player_Legs");
	_playerInfo.HeadArmor = NULL;
	_playerInfo.BodyArmor = NULL;
	_playerInfo.LegsArmor = NULL;

	_gravity = 0.05f;
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	int mouse = MaxTile_Y * ((((_ptMouse.x + _playerInfo.rect.left) - WINSIZEX / 2) / TILESIZE) + 1) + ((((_ptMouse.y + _playerInfo.rect.top) - WINSIZEY / 2) / TILESIZE) + 1);
	BlockCollision();
	Action();
	Frame();

	/*마우스 위치 블럭 파괴 공식
	_vTile[MaxTile_Y * ((((_ptMouse.x + _playerInfo.rect.left)-WINSIZEX/2) / TILESIZE)+1) + ((((_ptMouse.y + _playerInfo.rect.top)-WINSIZEY/2) / TILESIZE)+1)]->blockType = BlockType::NONE;*/
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) 
		&& _vTile[mouse]->blockType == BlockType::NONE 
		&& _vTile[mouse]->objectType == ObjectType::NONE)
	{
		_vTile[mouse]->tileType = TileType::BLOCK;
		_vTile[mouse]->blockType = BlockType::DIRT;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON)
		&& _vTile[mouse]->tileType == TileType::BLOCK)
	{
		_vTile[mouse]->tileType = TileType::NONE;
		_vTile[mouse]->blockType = BlockType::NONE;
	}
	//_jump->update(_playerInfo.Down,_playerInfo.Up);

	PlayerInfoUpdate();
	CAMERAMANAGER->setCameraPos(_playerInfo.x - WINSIZEX / 2, _playerInfo.y - WINSIZEY / 2);
}

void Player::render()
{
	//Rectangle(CAMERAMANAGER->getCameraDC(), _vTile[MaxTile_Y * (_playerInfo.index.x + 0) + _playerInfo.index.y + 3]->rc);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y + 3]->rc);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 3]->rc);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.rect);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.Lrect);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.Trect);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.Rrect);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.Brect);
	switch (_playerInfo.HeadState)
	{
	case PlayerHeadState::IDLE:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	case PlayerHeadState::MOVE:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	case PlayerHeadState::JUMP:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	case PlayerHeadState::ATTACK:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	}
	_playerInfo.Legs->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.LegsFrameY);
}

void Player::PlayerInfoUpdate()
{
	_playerInfo.rect = RectMakeCenter(_playerInfo.x, _playerInfo.y, 60, 85);
	_playerInfo.Lrect = RectMake(_playerInfo.rect.left - 1, _playerInfo.rect.top, 1, getRectHeight(_playerInfo.rect));
	_playerInfo.Rrect = RectMake(_playerInfo.rect.right, _playerInfo.rect.top, 1, getRectHeight(_playerInfo.rect));
	_playerInfo.Trect = RectMake(_playerInfo.rect.left, _playerInfo.rect.top - 1, getRectWidth(_playerInfo.rect), 1);
	_playerInfo.Brect = RectMake(_playerInfo.rect.left, _playerInfo.rect.bottom, getRectWidth(_playerInfo.rect), 1);
	_playerInfo.index.x = (_playerInfo.rect.left + 15) / TILESIZE;
	_playerInfo.index.y = _playerInfo.rect.top / TILESIZE;
}

void Player::Action()
{
	if (_playerInfo.Up)
	{
		_playerInfo.jump = false;
	}
	if (_playerInfo.Down)
	{
		_gravity = 0;
		_playerInfo.jump = false;
		//cout << "밑블록" << endl;
	}
	else
	{
		_gravity -= 0.25f;
		if (_gravity <= -40)_gravity = -40;
	}
	_playerInfo.y -= _gravity;
	if (KEYMANAGER->isStayKeyDown('A') && _playerInfo.x - getRectWidth(_playerInfo.rect) / 2 >= 0 && !_playerInfo.Left)
	{
		_playerInfo.direction = PlayerDirection::LEFT;
		_playerInfo.HeadState = PlayerHeadState::MOVE;
		_playerInfo.BodyState = PlayerBodyState::MOVE;
		_playerInfo.LegsState = PlayerLegsState::MOVE;
		_playerInfo.x -= 5;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_playerInfo.direction = PlayerDirection::LEFT;
		_playerInfo.HeadState = PlayerHeadState::IDLE;
		_playerInfo.BodyState = PlayerBodyState::IDLE;
		_playerInfo.LegsState = PlayerLegsState::IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D') && _playerInfo.x + getRectWidth(_playerInfo.rect) / 2 <= TILESIZE * MaxTile_X && !_playerInfo.Right)
	{
		_playerInfo.direction = PlayerDirection::RIGHT;
		_playerInfo.HeadState = PlayerHeadState::MOVE;
		_playerInfo.BodyState = PlayerBodyState::MOVE;
		_playerInfo.LegsState = PlayerLegsState::MOVE;
		_playerInfo.x += 5;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_playerInfo.direction = PlayerDirection::RIGHT;
		_playerInfo.HeadState = PlayerHeadState::IDLE;
		_playerInfo.BodyState = PlayerBodyState::IDLE;
		_playerInfo.LegsState = PlayerLegsState::IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('W') && !_playerInfo.Up)
	{
		_playerInfo.y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('S') && !_playerInfo.Down)
	{
		_playerInfo.y += 5;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//_jump->jumping(&_playerInfo.x, &_playerInfo.y,20, 0.5f);
		_playerInfo.jump = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_playerInfo.BodyState = PlayerBodyState::ATTACK;
	}
	CAMERAMANAGER->setCameraPos(_playerInfo.x - WINSIZEX / 2, _playerInfo.y - WINSIZEY / 2);
	if (_playerInfo.jump)
	{
		_playerInfo.y -= 10;
	}

}

void Player::Frame()
{
	_playerInfo.FrameCount += TIMEMANAGER->getElapsedTime();
	switch (_playerInfo.direction)
	{
	case PlayerDirection::LEFT:
		_playerInfo.FrameX = 0;
		break;
	case PlayerDirection::RIGHT:
		_playerInfo.FrameX = 1;
		break;
	}
	if (_playerInfo.FrameCount >= 0.05f)
	{
		if (_playerInfo.HeadFrameY >= 19)_playerInfo.HeadFrameY = 6;
		if (_playerInfo.BodyFrameY >= 19)_playerInfo.BodyFrameY = 6;
		if (_playerInfo.LegsFrameY >= 19)_playerInfo.LegsFrameY = 6;
		_playerInfo.HeadFrameY++;
		_playerInfo.BodyFrameY++;
		_playerInfo.LegsFrameY++;
		/*switch (_playerInfo.BodyState)
		{
		case PlayerBodyState::IDLE:
			_playerInfo.BodyFrameY = 0;
			break;
		case PlayerBodyState::MOVE:
			if (_playerInfo.BodyFrameY < 6 && _playerInfo.BodyFrameY >= 19)_playerInfo.BodyFrameY = 6;
			_playerInfo.BodyFrameY++;
			break;
		case PlayerBodyState::JUMP:
			_playerInfo.BodyFrameY = 5;
			break;
		case PlayerBodyState::ATTACK:
			break;
		default:
			break;
		}

		switch (_playerInfo.LegsState)
		{
		case PlayerLegsState::IDLE:
			break;
		case PlayerLegsState::MOVE:
			break;
		case PlayerLegsState::JUMP:
			break;
		case PlayerLegsState::ATTACK:
			break;
		}*/
		_playerInfo.FrameCount = 0;
	}


}

void Player::BlockCollision()
{
	LeftBlockCollision();
	RightBlockCollision();
	UpBlockCollision();
	DownBlockCollision();
}

void Player::LeftBlockCollision()
{
	RECT temp;
	BlockType	LeftBlockType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->blockType;
	BlockType	LeftBlockType2 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 1]->blockType;
	BlockType	LeftBlockType3 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 2]->blockType;
	TileType	LeftTileType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->tileType;
	TileType	LeftTileType2 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 1]->tileType;
	TileType	LeftTileType3 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 2]->tileType;
	RECT		LeftTileRect1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->rc;
	RECT		LeftTileRect2 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 1]->rc;
	RECT		LeftTileRect3 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 2]->rc;
	if ((LeftTileType1 == TileType::BLOCK && LeftBlockType1 != BlockType::NONE && IntersectRect(&temp, &LeftTileRect1, &_playerInfo.Lrect)) ||
		(LeftTileType2 == TileType::BLOCK && LeftBlockType2 != BlockType::NONE && IntersectRect(&temp, &LeftTileRect2, &_playerInfo.Lrect)) ||
		(LeftTileType3 == TileType::BLOCK && LeftBlockType3 != BlockType::NONE && IntersectRect(&temp, &LeftTileRect3, &_playerInfo.Lrect)))
	{
		_playerInfo.Left = true;
		//cout << "왼쪽 블럭" << endl;
	}
	else
	{
		_playerInfo.Left = false;
	}


}

void Player::RightBlockCollision()
{
	RECT temp;
	BlockType	RightBlockType1 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y]->blockType;
	BlockType	RightBlockType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 1]->blockType;
	BlockType	RightBlockType3 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 2]->blockType;
	TileType	RightTileType1 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y]->tileType;
	TileType	RightTileType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 1]->tileType;
	TileType	RightTileType3 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 2]->tileType;
	RECT		RightTileRect1 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y]->rc;
	RECT		RightTileRect2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 1]->rc;
	RECT	    RightTileRect3 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 2]->rc;
	if ((RightTileType1 == TileType::BLOCK && RightBlockType1 != BlockType::NONE && IntersectRect(&temp, &RightTileRect1, &_playerInfo.Rrect)) ||
		(RightTileType2 == TileType::BLOCK && RightBlockType2 != BlockType::NONE && IntersectRect(&temp, &RightTileRect2, &_playerInfo.Rrect)) ||
		(RightTileType3 == TileType::BLOCK && RightBlockType3 != BlockType::NONE && IntersectRect(&temp, &RightTileRect3, &_playerInfo.Rrect)))
	{
		//_playerInfo.x = RightTileRect3.left - _playerInfo.Head->getFrameWidth() / 2;
		_playerInfo.Right = true;
		//cout << "오른쪽 블럭" << endl;
	}
	else
	{
		_playerInfo.Right = false;
	}

}

void Player::UpBlockCollision()
{
	RECT temp;
	BlockType	upBlockType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->blockType;
	BlockType	upBlockType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y]->blockType;
	TileType	upTileType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->tileType;
	TileType	upTileType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y]->tileType;
	RECT		upTileRect1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->rc;
	RECT		upTileRect2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y]->rc;
	if ((upTileType1 == TileType::BLOCK && upBlockType1 != BlockType::NONE && IntersectRect(&temp, &upTileRect1, &_playerInfo.Trect)) ||
		(upTileType2 == TileType::BLOCK && upBlockType2 != BlockType::NONE && IntersectRect(&temp, &upTileRect2, &_playerInfo.Trect)))
	{
		_playerInfo.Up = true;
		_playerInfo.y = upTileRect1.bottom + getRectHeight(_playerInfo.rect) / 2;
		//cout << "위 블럭" << endl;
	}
	else
	{
		_playerInfo.Up = false;
	}
}

void Player::DownBlockCollision()
{
	RECT temp;
	BlockType downBlockType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 3]->blockType;
	BlockType downBlockType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y + 3]->blockType;
	TileType downTileType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 3]->tileType;
	TileType downTileType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y + 3]->tileType;
	RECT	 downTileRect1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 3]->rc;
	RECT	 downTileRect2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y + 3]->rc;
	if ((downTileType1 == TileType::BLOCK && downBlockType1 != BlockType::NONE && IntersectRect(&temp, &downTileRect1, &_playerInfo.Brect)) ||
		(downTileType2 == TileType::BLOCK && downBlockType2 != BlockType::NONE && IntersectRect(&temp, &downTileRect2, &_playerInfo.Brect)))
	{
		_playerInfo.Down = true;
		_playerInfo.y = downTileRect1.top - (getRectHeight(_playerInfo.rect)) / 2;
		//cout << "밑에 블럭" << endl;
	}
	else
	{
		_playerInfo.Down = false;
	}

}

int Player::getStartX()
{
	if (0 >= (_playerInfo.x - TILESIZE * 3 - WINSIZEX / 2) / TILESIZE)return 0;
	else return(_playerInfo.x - TILESIZE * 1 - WINSIZEX / 2) / TILESIZE;
}
int Player::getEndX()
{
	if (MaxTile_X <= (_playerInfo.x + TILESIZE * 3 + WINSIZEX / 2) / TILESIZE)return MaxTile_X;
	else return(_playerInfo.x + TILESIZE * 1 + WINSIZEX / 2) / TILESIZE;
}
int Player::getStartY()
{
	if (0 >= (_playerInfo.y - TILESIZE * 3 - WINSIZEY / 2) / TILESIZE)return 0;
	else return(_playerInfo.y - TILESIZE * 1 - WINSIZEY / 2) / TILESIZE;
}
int Player::getEndY()
{
	if (MaxTile_Y <= (_playerInfo.y + TILESIZE * 3 + WINSIZEY / 2) / TILESIZE)return MaxTile_Y;
	else return(_playerInfo.y + TILESIZE * 3 + WINSIZEY / 2) / TILESIZE;
}