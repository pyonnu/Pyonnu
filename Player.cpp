#include "stdafx.h"
#include "Player.h"
#include"EnemyManager.h"
HRESULT Player::init()
{
	_jump = new Jump;
	_move = new Move;
	//_jump->init(&_playerInfo.y);
	_move->init();

	_enemyManager = new EnemyManager;

	//_playerInfo = new PlayerInfo;

	_playerInfo.direction = PlayerDirection::RIGHT;
	_playerInfo.HeadState = PlayerState::IDLE;
	_playerInfo.BodyState = PlayerState::IDLE;
	_playerInfo.LegsState = PlayerState::IDLE;

	_playerInfo.FrameCount = 0;
	_playerInfo.FrameX = 0;
	_playerInfo.HeadFrameY = 0;
	_playerInfo.BodyFrameY = 0;
	_playerInfo.LegsFrameY = 0;
	
	_playerInfo.x = MaxTile_X * TILESIZE / 2;
	_playerInfo.y = MaxTile_Y * TILESIZE / 2/2;
	_playerInfo.rect = RectMake(_playerInfo.x, _playerInfo.y, 60, 96);

	_playerInfo.Head = IMAGEMANAGER->findImage("Player_Head");
	_playerInfo.Body = IMAGEMANAGER->findImage("Player_Body");
	_playerInfo.Legs = IMAGEMANAGER->findImage("Player_Legs");
	_playerInfo.HeadArmor = NULL;
	_playerInfo.BodyArmor = NULL;
	_playerInfo.LegsArmor = NULL;

	_playerInfo.Attack = false;
	_playerInfo.angle = 0;
	_playerInfo.attackSpeed = 0.12f;
	_playerInfo.MaxHealth = 100;
	_playerInfo.Health = 100;
	_gravity = 0.05f;
	ITEMMANAGER->CreateItem(_playerInfo.x+200,_playerInfo.y, type::COPPER_PICKAXE, ItemType::PICKAXE, IMAGEMANAGER->findImage("Item_14"), 4.0f,10,35);
	//ITEMMANAGER->CreateItem(_playerInfo.x+200, _playerInfo.y, type::COPPER_AXE, ItemType::AXE, IMAGEMANAGER->findImage("Item_15"), 3.0f);
	//ITEMMANAGER->CreateItem(_playerInfo.x+200, _playerInfo.y, type::COPPER_HAMMER, ItemType::HAMMER, IMAGEMANAGER->findImage("Item_16"), 4.0f);
	//ITEMMANAGER->CreateItem(_playerInfo.x+200, _playerInfo.y, type::COPPER_SWORD, ItemType::SWORD, IMAGEMANAGER->findImage("Item_17"), 8.0f);

	//Load();
	
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	_vItem = ITEMMANAGER->getVItem();
	_viItem = ITEMMANAGER->getViItem();
	int mouse = MaxTile_Y * ((((_ptMouse.x + _playerInfo.rect.left) - WINSIZEX / 2) / TILESIZE) + 1) + ((((_ptMouse.y + _playerInfo.rect.top) - WINSIZEY / 2) / TILESIZE) + 1);
	BlockCollision();
	ItemCollision();

	Action();
	Attack(mouse);

	Frame();
	
	//TileDestroyCreate(mouse);
	
	PlayerInfoUpdate();
	CAMERAMANAGER->setCameraPos(_playerInfo.x - WINSIZEX / 2, _playerInfo.y - WINSIZEY / 2);
	ITEMMANAGER->setVItem(_vItem);
	ITEMMANAGER->setViItem(_viItem);
	if (KEYMANAGER->isOnceKeyDown(VK_F1))Save();
	if (KEYMANAGER->isOnceKeyDown(VK_F2))Load();
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
	case PlayerState::IDLE:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	case PlayerState::MOVE:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	case PlayerState::JUMP:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	case PlayerState::ATTACK:
		_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.HeadFrameY);
		_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.BodyFrameY);
		break;
	}
	_playerInfo.Legs->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left - 10, _playerInfo.rect.top - 20, _playerInfo.FrameX, _playerInfo.LegsFrameY);
	//Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.attackRect);
	if (_playerInfo.Attack)
	{
		_playerInfo.attackImage->rotateRender(CAMERAMANAGER->getCameraDC(), (_playerInfo.attackRect.left + _playerInfo.attackRect.right) / 2, (_playerInfo.attackRect.top + _playerInfo.attackRect.bottom) / 2, _playerInfo.angle-0.785398);
	}
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
		_playerInfo.HeadState = PlayerState::IDLE;
		if(_playerInfo.BodyState!=PlayerState::ATTACK)_playerInfo.BodyState = PlayerState::IDLE;
		_playerInfo.LegsState = PlayerState::IDLE;
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
		if (_playerInfo.HeadState != PlayerState::JUMP)_playerInfo.HeadState = PlayerState::MOVE;
		if(_playerInfo.BodyState != PlayerState::ATTACK && _playerInfo.BodyState != PlayerState::JUMP)_playerInfo.BodyState = PlayerState::MOVE;
		if(_playerInfo.LegsState!=PlayerState::JUMP)_playerInfo.LegsState = PlayerState::MOVE;
		_playerInfo.x -= 5;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_playerInfo.direction = PlayerDirection::LEFT;
		_playerInfo.HeadState = PlayerState::IDLE;
		if (_playerInfo.BodyState == PlayerState::MOVE)_playerInfo.BodyState = PlayerState::IDLE;
		if (_playerInfo.LegsState == PlayerState::MOVE)_playerInfo.LegsState = PlayerState::IDLE;
	}
	if (KEYMANAGER->isStayKeyDown('D') && _playerInfo.x + getRectWidth(_playerInfo.rect) / 2 <= TILESIZE * MaxTile_X && !_playerInfo.Right)
	{
		_playerInfo.direction = PlayerDirection::RIGHT;

		if(_playerInfo.HeadState != PlayerState::JUMP)_playerInfo.HeadState = PlayerState::MOVE;
		if (_playerInfo.BodyState != PlayerState::ATTACK && _playerInfo.BodyState != PlayerState::JUMP)_playerInfo.BodyState = PlayerState::MOVE;
		if (_playerInfo.LegsState != PlayerState::JUMP)_playerInfo.LegsState = PlayerState::MOVE;
		_playerInfo.x += 5;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_playerInfo.direction = PlayerDirection::RIGHT;
		_playerInfo.HeadState = PlayerState::IDLE;
		if (_playerInfo.BodyState == PlayerState::MOVE)_playerInfo.BodyState = PlayerState::IDLE;
		if (_playerInfo.LegsState == PlayerState::MOVE)_playerInfo.LegsState = PlayerState::IDLE;

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
		_playerInfo.HeadState = PlayerState::JUMP;
		if (_playerInfo.BodyState != PlayerState::ATTACK)_playerInfo.BodyState = PlayerState::JUMP;
		_playerInfo.LegsState = PlayerState::JUMP;
		_playerInfo.jump = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)&& INVENTORYMANAGER->getItem() != NULL)
	{
		_playerInfo.HeadState = PlayerState::ATTACK;
		_playerInfo.BodyState = PlayerState::ATTACK;
		if (_playerInfo.LegsState != PlayerState::MOVE && _playerInfo.LegsState != PlayerState::JUMP)_playerInfo.LegsState = PlayerState::ATTACK;
		if (!_playerInfo.AttackIng)
		{
			_playerInfo.Attack = true;
			_playerInfo.AttackIng = true;
			switch (_playerInfo.direction)
			{
			case PlayerDirection::LEFT:
				_playerInfo.angle = 0;
				break;
			case PlayerDirection::RIGHT:
				_playerInfo.angle = PI;
				break;
			}
			_playerInfo.attackImage = INVENTORYMANAGER->getImage();
		}
	}
	CAMERAMANAGER->setCameraPos(_playerInfo.x - WINSIZEX / 2, _playerInfo.y - WINSIZEY / 2);
	if (_playerInfo.jump)
	{
		_playerInfo.y -= 10;
	}

}

void Player::Attack(int mouse)
{
	if (_playerInfo.currentDirection != _playerInfo.direction)
	{
		switch (_playerInfo.direction)
		{
		case PlayerDirection::LEFT:
			_playerInfo.angle = PI - _playerInfo.angle;
			break;
		case PlayerDirection::RIGHT:
			_playerInfo.angle = PI - _playerInfo.angle;

			break;
		}
	}
	if (_playerInfo.Attack)
	{
		switch (_playerInfo.direction)
		{
		case PlayerDirection::LEFT:
			_playerInfo.angle += _playerInfo.attackSpeed;
			if (_playerInfo.angle > PI-0.01f)
			{
				_playerInfo.angle = 0;
				_playerInfo.Attack = false;
				_playerInfo.AttackIng = false;
				TileDestroy(mouse);
				if (_playerInfo.LegsState == PlayerState::JUMP)_playerInfo.BodyState = PlayerState::JUMP;
				else _playerInfo.BodyState = PlayerState::IDLE;
			}
			break;
		case PlayerDirection::RIGHT:
			_playerInfo.angle -= _playerInfo.attackSpeed;
			if (_playerInfo.angle < 0.01f)
			{
				_playerInfo.angle = PI;
				_playerInfo.Attack = false;
				_playerInfo.AttackIng = false;
				TileDestroy(mouse);
				if (_playerInfo.LegsState == PlayerState::JUMP)_playerInfo.BodyState = PlayerState::JUMP;
				else _playerInfo.BodyState = PlayerState::IDLE;
			}
			break;
		}
	}
	//cout << _playerInfo.angle << endl;
	if (INVENTORYMANAGER->getItem() != NULL)
	{
		_playerInfo.attackX = cosf(_playerInfo.angle) * (INVENTORYMANAGER->getImage()->getWidth()/1.3) + _playerInfo.x;
		_playerInfo.attackY = -sinf(_playerInfo.angle) * (INVENTORYMANAGER->getImage()->getHeight()/1.3) + _playerInfo.y;
		_playerInfo.attackRect = RectMakeCenter(_playerInfo.attackX, _playerInfo.attackY, INVENTORYMANAGER->getImage()->getWidth(), INVENTORYMANAGER->getImage()->getHeight());
	}
	else
	{
		_playerInfo.attackRect.left = NULL;
		_playerInfo.attackRect.right = NULL;
		_playerInfo.attackRect.top = NULL;
		_playerInfo.attackRect.bottom = NULL;
	}
	_playerInfo.currentDirection = _playerInfo.direction;
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
	if (_playerInfo.FrameCount >= 0.12f)
	{
		switch (_playerInfo.HeadState)
		{
		case PlayerState::IDLE:
			_playerInfo.HeadFrameY = 0;
			break;
		case PlayerState::MOVE:
			if (_playerInfo.HeadFrameY < 6 || _playerInfo.HeadFrameY >= 19)_playerInfo.HeadFrameY = 6;
			_playerInfo.HeadFrameY++;
			break;
		case PlayerState::JUMP:
			_playerInfo.HeadFrameY = 5;
			break;
		case PlayerState::ATTACK:
			if (_playerInfo.HeadFrameY < 0 || _playerInfo.HeadFrameY >3)_playerInfo.HeadFrameY = 0;
			_playerInfo.HeadFrameY++;
			break;
		}

		switch (_playerInfo.BodyState)
		{
		case PlayerState::IDLE:
			_playerInfo.BodyFrameY = 0;
			break;
		case PlayerState::MOVE:
			if (_playerInfo.BodyFrameY < 6 || _playerInfo.BodyFrameY >= 19)_playerInfo.BodyFrameY = 6;
			_playerInfo.BodyFrameY++;
			break;
		case PlayerState::JUMP:
			_playerInfo.BodyFrameY = 5;
			break;
		case PlayerState::ATTACK:
			if (_playerInfo.BodyFrameY < 0 || _playerInfo.BodyFrameY >3)_playerInfo.BodyFrameY = 0;
			_playerInfo.BodyFrameY++;
			break;
		}

		switch (_playerInfo.LegsState)
		{
		case PlayerState::IDLE:
			_playerInfo.LegsFrameY = 0;
			break;
		case PlayerState::MOVE:
			if (_playerInfo.LegsFrameY < 6 || _playerInfo.LegsFrameY >= 19)_playerInfo.LegsFrameY = 6;
			_playerInfo.LegsFrameY++;
			break;
		case PlayerState::JUMP:
			_playerInfo.LegsFrameY = 5;
			break;
		case PlayerState::ATTACK:
			if (_playerInfo.LegsFrameY < 0 || _playerInfo.LegsFrameY >3)_playerInfo.LegsFrameY = 0;
			_playerInfo.LegsFrameY++;
			break;
		}

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

void Player::ItemCollision()
{
	RECT temp;
	for (_viItem = _vItem.begin();_viItem != _vItem.end();)
	{
		//cout << (*_viItem)->getRect().left << endl;
		if (IntersectRect(&temp, &(*_viItem)->getRect(), &_playerInfo.rect))
		{
			InventoryItemAdd(_viItem);
			_vItem.erase(_viItem);
			break;
		}
		else
		{
			++_viItem;
		}
	}
}

void Player::TileDestroyCreate(int mouse)
{
	if(_playerInfo.angle < 0.09 || _playerInfo.angle > PI-0.09)
	if (!PtInRect(&INVENTORYMANAGER->getRect(), _ptMouse) || !INVENTORYMANAGER->getInvenSee())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (INVENTORYMANAGER->getItem() != NULL)
			{
				switch (INVENTORYMANAGER->getItemType1())
				{
				case ItemType::BLOCK:
					if(_vTile[mouse]->block == TileType::NONE)
					switch (INVENTORYMANAGER->getitem())
					{
					case type::DIRT_BLOCK:
						cout << 1 << endl;
						_vTile[mouse]->blockBurglar = 50.0f;
						_vTile[mouse]->blockType = BlockType::DIRT;
						_vTile[mouse]->block = TileType::BLOCK;
						INVENTORYMANAGER->getItem()->removeItemStack(1);
						break;
					case type::STONE_BLOCK:
						cout << 2 << endl;
						_vTile[mouse]->blockBurglar = 100.0f;
						_vTile[mouse]->blockType = BlockType::STONE;
						_vTile[mouse]->block = TileType::BLOCK;
						INVENTORYMANAGER->getItem()->removeItemStack(1);
						break;
					case type::WOOD:
						cout << 3 << endl;
						_vTile[mouse]->blockBurglar = 100.0f;
						_vTile[mouse]->blockType = BlockType::WOOD;
						_vTile[mouse]->block = TileType::BLOCK;
						INVENTORYMANAGER->getItem()->removeItemStack(1);
						break;
					case type::COPPER:
						cout << 4 << endl;
						_vTile[mouse]->blockBurglar = 100.0f;
						_vTile[mouse]->blockType = BlockType::COPPER;
						_vTile[mouse]->block = TileType::BLOCK;
						INVENTORYMANAGER->getItem()->removeItemStack(1);
						break;
					case type::IRON:
						cout << 5 << endl;
						_vTile[mouse]->blockBurglar = 100.0f;
						_vTile[mouse]->blockType = BlockType::IRON;
						_vTile[mouse]->block = TileType::BLOCK;
						INVENTORYMANAGER->getItem()->removeItemStack(1);
						break;
					case type::GOLD:
						cout << 6 << endl;
						_vTile[mouse]->blockBurglar = 100.0f;
						_vTile[mouse]->blockType = BlockType::GOLD;
						_vTile[mouse]->block = TileType::BLOCK;
						INVENTORYMANAGER->getItem()->removeItemStack(1);
						break;
					case type::PLATINUM:
						cout << 7 << endl;
						_vTile[mouse]->blockBurglar = 150.0f;
						_vTile[mouse]->blockType = BlockType::PLATINUM;
						_vTile[mouse]->block = TileType::BLOCK;
						INVENTORYMANAGER->getItem()->removeItemStack(1);
						break;
					default:
						cout <<18<< endl;
						break;
					}
					break;
				case ItemType::WALL:
					switch (INVENTORYMANAGER->getitem())
					{
					case type::WOOD_WALL:
						_vTile[mouse]->wallType = WallType::WOOD;
						_vTile[mouse]->wall = TileType::WALL;
						break;
					case type::DIRT_WALL:
						_vTile[mouse]->wallType = WallType::DIRT;
						_vTile[mouse]->wall = TileType::WALL;
						break;
					case type::STONE_WALL:
						_vTile[mouse]->wallType = WallType::STONE;
						_vTile[mouse]->wall = TileType::WALL;
						break;
					default:
						break;
					}
					break;
				case ItemType::CONSUMBLE:
					switch (INVENTORYMANAGER->getitem())
					{
					case type::POTION50:
						if (_playerInfo.Health + 50 >= _playerInfo.MaxHealth)_playerInfo.Health = _playerInfo.MaxHealth;
						else _playerInfo.Health += 50;
						break;
					case type::POTION100:
						if (_playerInfo.Health + 100 >= _playerInfo.MaxHealth)_playerInfo.Health = _playerInfo.MaxHealth;
						else _playerInfo.Health += 100;
						break;
					case type::HEARTCRYSTAL:
						_playerInfo.MaxHealth += 20;
						break;
					default:
						break;
					}
					break;
				case ItemType::PICKAXE:
					_vTile[mouse]->blockBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					_vTile[mouse]->objectBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					cout << 1 << endl;
					break;
				case ItemType::AXE:
					_vTile[mouse]->objectBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					break;
				case ItemType::HAMMER:
					_vTile[mouse]->wallBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					break;
				case ItemType::SWORD:

					break;
				default:
					break;
				}
			}
		}
		
	}
}

void Player::TileDestroy(int mouse)
{
	if (!PtInRect(&INVENTORYMANAGER->getRect(), _ptMouse) || !INVENTORYMANAGER->getInvenSee())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (INVENTORYMANAGER->getItem() != NULL)
			{
				switch (INVENTORYMANAGER->getItemType1())
				{
				case ItemType::BLOCK:
					if (_vTile[mouse]->block == TileType::NONE)
						switch (INVENTORYMANAGER->getitem())
						{
						case type::DIRT_BLOCK:
							cout << 1 << endl;
							_vTile[mouse]->blockBurglar = 50.0f;
							_vTile[mouse]->blockType = BlockType::DIRT;
							_vTile[mouse]->block = TileType::BLOCK;
							INVENTORYMANAGER->getItem()->removeItemStack(1);
							break;
						case type::STONE_BLOCK:
							cout << 2 << endl;
							_vTile[mouse]->blockBurglar = 100.0f;
							_vTile[mouse]->blockType = BlockType::STONE;
							_vTile[mouse]->block = TileType::BLOCK;
							INVENTORYMANAGER->getItem()->removeItemStack(1);
							break;
						case type::WOOD:
							cout << 3 << endl;
							_vTile[mouse]->blockBurglar = 100.0f;
							_vTile[mouse]->blockType = BlockType::WOOD;
							_vTile[mouse]->block = TileType::BLOCK;
							INVENTORYMANAGER->getItem()->removeItemStack(1);
							break;
						case type::COPPER:
							cout << 4 << endl;
							_vTile[mouse]->blockBurglar = 100.0f;
							_vTile[mouse]->blockType = BlockType::COPPER;
							_vTile[mouse]->block = TileType::BLOCK;
							INVENTORYMANAGER->getItem()->removeItemStack(1);
							break;
						case type::IRON:
							cout << 5 << endl;
							_vTile[mouse]->blockBurglar = 100.0f;
							_vTile[mouse]->blockType = BlockType::IRON;
							_vTile[mouse]->block = TileType::BLOCK;
							INVENTORYMANAGER->getItem()->removeItemStack(1);
							break;
						case type::GOLD:
							cout << 6 << endl;
							_vTile[mouse]->blockBurglar = 100.0f;
							_vTile[mouse]->blockType = BlockType::GOLD;
							_vTile[mouse]->block = TileType::BLOCK;
							INVENTORYMANAGER->getItem()->removeItemStack(1);
							break;
						case type::PLATINUM:
							cout << 7 << endl;
							_vTile[mouse]->blockBurglar = 150.0f;
							_vTile[mouse]->blockType = BlockType::PLATINUM;
							_vTile[mouse]->block = TileType::BLOCK;
							INVENTORYMANAGER->getItem()->removeItemStack(1);
							break;
						default:
							cout << 18 << endl;
							break;
						}
					break;
				case ItemType::WALL:
					switch (INVENTORYMANAGER->getitem())
					{
					case type::WOOD_WALL:
						_vTile[mouse]->wallType = WallType::WOOD;
						_vTile[mouse]->wall = TileType::WALL;
						break;
					case type::DIRT_WALL:
						_vTile[mouse]->wallType = WallType::DIRT;
						_vTile[mouse]->wall = TileType::WALL;
						break;
					case type::STONE_WALL:
						_vTile[mouse]->wallType = WallType::STONE;
						_vTile[mouse]->wall = TileType::WALL;
						break;
					default:
						break;
					}
					break;
				case ItemType::CONSUMBLE:
					switch (INVENTORYMANAGER->getitem())
					{
					case type::POTION50:
						if (_playerInfo.Health + 50 >= _playerInfo.MaxHealth)_playerInfo.Health = _playerInfo.MaxHealth;
						else _playerInfo.Health += 50;
						break;
					case type::POTION100:
						if (_playerInfo.Health + 100 >= _playerInfo.MaxHealth)_playerInfo.Health = _playerInfo.MaxHealth;
						else _playerInfo.Health += 100;
						break;
					case type::HEARTCRYSTAL:
						_playerInfo.MaxHealth += 20;
						break;
					default:
						break;
					}
					break;
				case ItemType::PICKAXE:
					_vTile[mouse]->blockBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					_vTile[mouse]->objectBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					cout << _vTile[mouse]->blockBurglar << endl;
					cout << INVENTORYMANAGER->getItem()->getToolsPower() << endl;
					//cout << 1 << endl;
					break;
				case ItemType::AXE:
					_vTile[mouse]->objectBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					break;
				case ItemType::HAMMER:
					_vTile[mouse]->wallBurglar -= INVENTORYMANAGER->getItem()->getToolsPower();
					break;
				case ItemType::SWORD:

					break;
				default:
					break;
				}
			}
		}

	}
}

void Player::InventoryItemAdd(vector<Item*>::iterator viItem)
{
	switch ((*viItem)->getItemType())
	{
	case type::DIRT_BLOCK:
		INVENTORYMANAGER->ItemAdd("item_1", (*viItem));
		break;
	case type::STONE_BLOCK:
		INVENTORYMANAGER->ItemAdd("item_2", (*viItem));
		break;
	case type::WOOD:
		INVENTORYMANAGER->ItemAdd("item_3", (*viItem));
		break;
	case type::COPPER:
		INVENTORYMANAGER->ItemAdd("item_4", (*viItem));
		break;
	case type::COPPER_BAR:
		INVENTORYMANAGER->ItemAdd("item_5", (*viItem));
		break;
	case type::IRON:
		INVENTORYMANAGER->ItemAdd("item_6", (*viItem));
		break;
	case type::IRON_BAR:
		INVENTORYMANAGER->ItemAdd("item_7", (*viItem));
		break;
	case type::GOLD:
		INVENTORYMANAGER->ItemAdd("item_8", (*viItem));
		break;
	case type::GOLD_BAR:
		INVENTORYMANAGER->ItemAdd("item_9", (*viItem));
		break;
	case type::PLATINUM:
		INVENTORYMANAGER->ItemAdd("item_10", (*viItem));
		break;
	case type::PLATINUM_BAR:
		INVENTORYMANAGER->ItemAdd("item_11", (*viItem));
		break;
	case type::DEMONITE:
		INVENTORYMANAGER->ItemAdd("item_12", (*viItem));
		break;
	case type::DEMONITE_BAR:
		INVENTORYMANAGER->ItemAdd("item_13", (*viItem));
		break;
	case type::COPPER_PICKAXE:
		INVENTORYMANAGER->ItemAdd("item_14", (*viItem));
		break;
	case type::COPPER_AXE:
		INVENTORYMANAGER->ItemAdd("item_15", (*viItem));
		break;
	case type::COPPER_HAMMER:
		INVENTORYMANAGER->ItemAdd("item_16", (*viItem));
		break;
	case type::COPPER_SWORD:
		INVENTORYMANAGER->ItemAdd("item_17", (*viItem));
		break;
	case type::IRON_PICKAXE:
		INVENTORYMANAGER->ItemAdd("item_18", (*viItem));
		break;
	case type::IRON_AXE:
		INVENTORYMANAGER->ItemAdd("item_19", (*viItem));
		break;
	case type::IRON_HAMMER:
		INVENTORYMANAGER->ItemAdd("item_20", (*viItem));
		break;
	case type::IRON_SWORD:
		INVENTORYMANAGER->ItemAdd("item_21", (*viItem));
		break;
	case type::GOLD_PICKAXE:
		INVENTORYMANAGER->ItemAdd("item_22", (*viItem));
		break;
	case type::GOLD_AXE:
		INVENTORYMANAGER->ItemAdd("item_23", (*viItem));
		break;
	case type::GOLD_HAMMER:
		INVENTORYMANAGER->ItemAdd("item_24", (*viItem));
		break;
	case type::GOLD_SWORD:
		INVENTORYMANAGER->ItemAdd("item_25", (*viItem));
		break;
	case type::PLATINUM_PICKAXE:
		INVENTORYMANAGER->ItemAdd("item_26", (*viItem));
		break;
	case type::PLATINUM_AXE:
		INVENTORYMANAGER->ItemAdd("item_27", (*viItem));
		break;
	case type::PLATINUM_HAMMER:
		INVENTORYMANAGER->ItemAdd("item_28", (*viItem));
		break;
	case type::PLATINUM_SWORD:
		INVENTORYMANAGER->ItemAdd("item_29", (*viItem));
		break;
	case type::DEMONITE_PICKAXE:
		INVENTORYMANAGER->ItemAdd("item_30", (*viItem));
		break;
	case type::DEMONITE_AXE:
		INVENTORYMANAGER->ItemAdd("item_31", (*viItem));
		break;
	case type::DEMONITE_HAMMER:
		INVENTORYMANAGER->ItemAdd("item_32", (*viItem));
		break;
	case type::DEMONITE_SWORD:
		INVENTORYMANAGER->ItemAdd("item_33", (*viItem));
		break;
	case type::COPPER_HELMET:
		INVENTORYMANAGER->ItemAdd("item_34", (*viItem));
		break;
	case type::COPPER_ARMOR:
		INVENTORYMANAGER->ItemAdd("item_35", (*viItem));
		break;
	case type::COPPER_LEGGINGS:
		INVENTORYMANAGER->ItemAdd("item_36", (*viItem));
		break;
	case type::IRON_HELMET:
		INVENTORYMANAGER->ItemAdd("item_37", (*viItem));
		break;
	case type::IRON_ARMOR:
		INVENTORYMANAGER->ItemAdd("item_38", (*viItem));
		break;
	case type::IRON_LEGGINGS:
		INVENTORYMANAGER->ItemAdd("item_39", (*viItem));
		break;
	case type::GOLD_HELMET:
		INVENTORYMANAGER->ItemAdd("item_40", (*viItem));
		break;
	case type::GOLD_ARMOR:
		INVENTORYMANAGER->ItemAdd("item_41", (*viItem));
		break;
	case type::GOLD_LEGGINGS:
		INVENTORYMANAGER->ItemAdd("item_42", (*viItem));
		break;
	case type::PLATINUM_HELMET:
		INVENTORYMANAGER->ItemAdd("item_43", (*viItem));
		break;
	case type::PLATINUM_ARMOR:
		INVENTORYMANAGER->ItemAdd("item_44", (*viItem));
		break;
	case type::PLATINUM_LEGGINGS:
		INVENTORYMANAGER->ItemAdd("item_45", (*viItem));
		break;
	case type::DEMONITE_HELMET:
		INVENTORYMANAGER->ItemAdd("item_46", (*viItem));
		break;
	case type::DEMONITE_ARMOR:
		INVENTORYMANAGER->ItemAdd("item_47", (*viItem));
		break;
	case type::DEMONITE_LEGGINGS:
		INVENTORYMANAGER->ItemAdd("item_48", (*viItem));
		break;
	case type::COPPER_COIN:
		INVENTORYMANAGER->ItemAdd("item_49", (*viItem));
		break;
	case type::IRON_COIN:
		INVENTORYMANAGER->ItemAdd("item_50", (*viItem));
		break;
	case type::GOLD_COIN:
		INVENTORYMANAGER->ItemAdd("item_51", (*viItem));
		break;
	case type::PLATINUM_COIN:
		INVENTORYMANAGER->ItemAdd("item_52", (*viItem));
		break;
	case type::DESK:
		INVENTORYMANAGER->ItemAdd("item_53", (*viItem));
		break;
	case type::FURNACE:
		INVENTORYMANAGER->ItemAdd("item_54", (*viItem));
		break;
	case type::WORKBENCH:
		INVENTORYMANAGER->ItemAdd("item_55", (*viItem));
		break;
	case type::ANVIL:
		INVENTORYMANAGER->ItemAdd("item_56", (*viItem));
		break;
	case type::CHIR:
		INVENTORYMANAGER->ItemAdd("item_57", (*viItem));
		break;
	case type::BOX:
		INVENTORYMANAGER->ItemAdd("item_58", (*viItem));
		break;
	case type::DOOR:
		INVENTORYMANAGER->ItemAdd("item_59", (*viItem));
		break;
	case type::WOOD_WALL:
		INVENTORYMANAGER->ItemAdd("item_60", (*viItem));
		break;
	case type::GEL:
		INVENTORYMANAGER->ItemAdd("item_61", (*viItem));
		break;
	case type::LENS:
		INVENTORYMANAGER->ItemAdd("item_62", (*viItem));
		break;
	case type::DEMONEYE:
		INVENTORYMANAGER->ItemAdd("item_63", (*viItem));
		break;
	case type::POTION50:
		INVENTORYMANAGER->ItemAdd("item_64", (*viItem));
		break;
	case type::POTION100:
		INVENTORYMANAGER->ItemAdd("item_65", (*viItem));
		break;
	case type::ACORN:
		INVENTORYMANAGER->ItemAdd("item_66", (*viItem));
		break;
	case type::HEARTCRYSTAL:
		INVENTORYMANAGER->ItemAdd("item_67", (*viItem));
		break;
	case type::DIRT_WALL:
		INVENTORYMANAGER->ItemAdd("item_68", (*viItem));
		break;
	case type::STONE_WALL:
		INVENTORYMANAGER->ItemAdd("item_69", (*viItem));
		break;
	default:
		break;
	}
}

void Player::LeftBlockCollision()
{
	RECT temp;
	BlockType	LeftBlockType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->blockType;
	BlockType	LeftBlockType2 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 1]->blockType;
	BlockType	LeftBlockType3 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 2]->blockType;
	TileType	LeftTileType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->block;
	TileType	LeftTileType2 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 1]->block;
	TileType	LeftTileType3 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 2]->block;
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
	TileType	RightTileType1 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y]->block;
	TileType	RightTileType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 1]->block;
	TileType	RightTileType3 = _vTile[MaxTile_Y * (_playerInfo.index.x + 2) + _playerInfo.index.y + 2]->block;
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
	TileType	upTileType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y]->block;
	TileType	upTileType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y]->block;
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
	TileType downTileType1 = _vTile[MaxTile_Y * _playerInfo.index.x + _playerInfo.index.y + 3]->block;
	TileType downTileType2 = _vTile[MaxTile_Y * (_playerInfo.index.x + 1) + _playerInfo.index.y + 3]->block;
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

void Player::Save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("PlayerSaveFile.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &_playerInfo, sizeof(PlayerInfo), &write, NULL);

	CloseHandle(file);
}

void Player::Load()
{
	HANDLE file;
	DWORD read;
	ZeroMemory(&_playerInfo, sizeof(_playerInfo));

	file = CreateFile("PlayerSaveFile.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_playerInfo, sizeof(PlayerInfo), &read, NULL);

	CloseHandle(file);
}