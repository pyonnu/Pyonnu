#include "stdafx.h"
#include "Player.h"
#include"EnemyManager.h"
HRESULT Player::init()
{
	_jump = new Jump;
	_move = new Move;
	_attack = new Attack;
	_item = new Item;

	_jump->init();
	_move->init();
	_attack->init();
	_item->init();

	_enemyManager = new EnemyManager;

	_playerInfo.direction = PlayerDirection::RIGHT;

	_playerInfo.FrameCount = 0;
	_playerInfo.FrameX = 0;
	_playerInfo.HeadFrameY = 0;
	_playerInfo.BodyFrameY = 0;
	_playerInfo.LegsFrameY = 0;

	_playerInfo.x = WINSIZEX / 2;
	_playerInfo.y = 1650;
	_playerInfo.rect = RectMake(_playerInfo.x, _playerInfo.y, 60, 96);
	
	_playerInfo.Head = IMAGEMANAGER->findImage("Player_Head");
	_playerInfo.Body = IMAGEMANAGER->findImage("Player_Body");
	_playerInfo.Legs = IMAGEMANAGER->findImage("Player_Legs");
	_playerInfo.dRect = RectMake(_playerInfo.x, _playerInfo.rect.bottom, _playerInfo.Head->getFrameWidth(), 10);
	_playerInfo.HeadArmor = NULL;
	_playerInfo.BodyArmor = NULL;
	_playerInfo.LegsArmor = NULL;

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	
	
	//cout << _mTile.find(&_playerInfo.D1Index)->second->rc.left << endl;
	
	Action();
	Frame();

	BlockCollision();
	_jump->update();
	_playerInfo.rect = RectMake(_playerInfo.x, _playerInfo.y, _playerInfo.Head->getFrameWidth(), _playerInfo.Head->getFrameHeight() - 18);
	_playerInfo.dRect = RectMake(_playerInfo.x, _playerInfo.rect.bottom, _playerInfo.Head->getFrameWidth(), 10);
	

	CAMERAMANAGER->setCameraPos(_playerInfo.x - WINSIZEX / 2, _playerInfo.y - WINSIZEY / 2);
}

void Player::render()
{
	Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.rect);
	Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.dRect);
	_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left, _playerInfo.rect.top - 15, _playerInfo.FrameX, _playerInfo.HeadFrameY);
	_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left, _playerInfo.rect.top - 15, _playerInfo.FrameX, _playerInfo.BodyFrameY);
	_playerInfo.Legs->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left, _playerInfo.rect.top - 15, _playerInfo.FrameX, _playerInfo.LegsFrameY);
}

void Player::PlayerIndexUpdate()
{
	_playerInfo.index.x = _playerInfo.x / TILESIZE;
	_playerInfo.index.y = _playerInfo.y / TILESIZE;

	_playerInfo.L1Index.x = _playerInfo.index.x - 1;
	_playerInfo.L1Index.y = _playerInfo.index.y;
	_playerInfo.L2Index.x = _playerInfo.index.x - 1;
	_playerInfo.L2Index.y = _playerInfo.index.y + 1;
	_playerInfo.L3Index.x = _playerInfo.index.x - 1;
	_playerInfo.L3Index.y = _playerInfo.index.y + 2;

	_playerInfo.R1Index.x = _playerInfo.index.x + 2;
	_playerInfo.R1Index.y = _playerInfo.index.y;
	_playerInfo.R2Index.x = _playerInfo.index.x + 2;
	_playerInfo.R2Index.y = _playerInfo.index.y + 1;
	_playerInfo.R3Index.x = _playerInfo.index.x + 2;
	_playerInfo.R3Index.y = _playerInfo.index.y + 2;

	_playerInfo.U1Index.x = _playerInfo.index.x;
	_playerInfo.U1Index.y = _playerInfo.index.y - 1;
	_playerInfo.U2Index.x = _playerInfo.index.x + 1;
	_playerInfo.U2Index.y = _playerInfo.index.y - 1;

	_playerInfo.D1Index.x = _playerInfo.index.x;
	_playerInfo.D1Index.y = _playerInfo.index.y + 3;
	_playerInfo.D2Index.x = _playerInfo.index.x + 1;
	_playerInfo.D2Index.y = _playerInfo.index.y + 3;

}

void Player::Action()
{
	if (_playerInfo.Down)
	{
		_playerInfo.y;
	}
	else
	{
		//중력 적용
	}
	if (KEYMANAGER->isStayKeyDown('A') && _playerInfo.x >= 0)
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
	if (KEYMANAGER->isStayKeyDown('D') && _playerInfo.x <= TILESIZE * MaxTile_X)
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
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_jump->jumping(&_playerInfo.x, &_playerInfo.y, 10, 0.5f);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_playerInfo.BodyState = PlayerBodyState::ATTACK;
	}
	CAMERAMANAGER->setCameraPos(_playerInfo.x - WINSIZEX / 2, _playerInfo.y - WINSIZEY / 2);
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
	//LeftBlockCollision();
	//RightBlockCollision();
	//UpBlockCollision();
	DownBlockCollision();
}

void Player::LeftBlockCollision()
{
	/*if (_mTile.find(&_playerInfo.L1Index)->second->tileType == TileType::BLOCK)
	{
		_mTile.find(&_playerInfo.L1Index)->second->rc;
	}
	if (_mTile.find(&_playerInfo.L2Index)->second->tileType == TileType::BLOCK)
	{
		_mTile.find(&_playerInfo.L2Index)->second->rc;
	}
	if (_mTile.find(&_playerInfo.L3Index)->second->tileType == TileType::BLOCK)
	{
		_mTile.find(&_playerInfo.L3Index)->second->rc;
	}*/
}

void Player::RightBlockCollision()
{

}

void Player::UpBlockCollision()
{
}

void Player::DownBlockCollision()
{
	RECT temp;

}
