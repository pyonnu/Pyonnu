#include "stdafx.h"
#include "EnemyManager.h"
#include"Player.h"
HRESULT EnemyManager::init()
{
	_spawnTimer = 0;
	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->setPlayerPos(_player->getPlayerInfo().rect, _player->getPlayerInfo().x, _player->getPlayerInfo().y);
		(*_viEnemy)->update();
		
	}
	enemyRemove();
	collision();
	EnemyCreate();
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SlimeCreate();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		ZombieCreate();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		DemonEyeCreate();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		DemonCreate();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		BossCreate();
	}
}

void EnemyManager::render()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->render();
	}

}

void EnemyManager::EnemyCreate()
{
	_spawnTimer += TIMEMANAGER->getElapsedTime();
	if (_spawnTimer >= RND->getFromFloatTo(2, 10))
	{
		int rnd = RND->getInt(3);
		if (rnd == 0)
		{
			ZombieCreate();
		}
		else if (rnd == 1)
		{
			DemonEyeCreate();
		}
		else if (rnd == 2)
		{
			DemonCreate();
		}
		_spawnTimer = 0;
	}
}

void EnemyManager::SlimeCreate()
{
	Enemy* enemy;
	enemy = new Slime;
	int rnd = RND->getInt(2);
	if (rnd == 0)
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x - 1300, _player->getPlayerInfo().y, 3, 14, 6, 0, "Slime", Type::SLIME);
	}
	else if (rnd == 1)
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x + 1300, _player->getPlayerInfo().y, 3, 14, 6, 0, "Slime", Type::SLIME);
	}

	_vEnemy.push_back(enemy);
}

void EnemyManager::DemonEyeCreate()
{
	Enemy* enemy;
	enemy = new DemonEye;
	int rnd = RND->getInt(2);
	if (rnd == 0)
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x + RND->getFromFloatTo(200,400), _player->getPlayerInfo().y - RND->getFromFloatTo(50, 200), 3, 60, 18, 2, "DemonEye", Type::DEMONEYE);
	}
	else
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x - RND->getFromFloatTo(200,400), _player->getPlayerInfo().y - RND->getFromFloatTo(50, 200), 3, 60, 18, 2, "DemonEye", Type::DEMONEYE);
	}
	
	_vEnemy.push_back(enemy);
}

void EnemyManager::DemonCreate()
{
	Enemy* enemy;
	enemy = new Demon;
	int rnd = RND->getInt(2);
	if (rnd == 0)
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x+ RND->getFromFloatTo(200,400), _player->getPlayerInfo().y - RND->getFromFloatTo(50, 200), 3, 120, 32, 8, "Demon", Type::DEMON);
	}
	else
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x- RND->getFromFloatTo(200, 400), _player->getPlayerInfo().y - RND->getFromFloatTo(50, 200), 3, 120, 32, 8, "Demon", Type::DEMON);
	}
	
	_vEnemy.push_back(enemy);
}

void EnemyManager::ZombieCreate()
{
	Enemy* enemy;
	enemy = new Zombie;
	int rnd = RND->getInt(2);
	if (rnd == 0)
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x + RND->getFromFloatTo(200,400), _player->getPlayerInfo().y - 10, 3, 45, 14, 6, "Zombie", Type::ZOMBIE);
	}
	else
	{
		enemy->EnemyCreate(_player->getPlayerInfo().x - RND->getFromFloatTo(200, 400), _player->getPlayerInfo().y - 10, 3, 45, 14, 6, "Zombie", Type::ZOMBIE);
	}
	
	_vEnemy.push_back(enemy);
}

void EnemyManager::BossCreate()
{
	Enemy* enemy;
	enemy = new EyeOfCthulhu;
	enemy->EnemyCreate(_player->getPlayerInfo().x, _player->getPlayerInfo().y, 3, 1400, 15, 12, "Boss", Type::BOSS);
	_vEnemy.push_back(enemy);
}

void EnemyManager::collision()
{
	RECT temp;

	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		LeftCollision(_viEnemy);
		TopCollision(_viEnemy);
		RightCollision(_viEnemy);
		BottomCollision(_viEnemy);


		if (IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->rc, &_player->getRect()))
		{
			_player->Hit((*_viEnemy)->getEnemyInfo()->damage,(*_viEnemy)->getEnemyInfo()->x);
			//cout << (*_viEnemy)->getEnemyInfo()->damage << endl;
		}
		else
		{
			_player->delaytReset();
		}
		if (IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->rc, &_player->getAttackRect()))
		{
			(*_viEnemy)->Hit(true, _player->getPlayerInfo().damage);
			//(*_viEnemy)->Knockback();
		}
		else
		{
			(*_viEnemy)->delayReset();
		}

	}
}

void EnemyManager::LeftCollision(vector<Enemy*>::iterator viEnemy)
{
	RECT temp;
	BlockType L1Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid]->blockType;
	BlockType L2Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid + 1]->blockType;
	BlockType L3Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid + 2]->blockType;
	BlockType L4Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid + 3]->blockType;
	RECT L1Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid]->rc;
	RECT L2Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid + 1]->rc;
	RECT L3Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid + 2]->rc;
	RECT L4Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->Tid + 3]->rc;
																									
	if ((L1Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Lrect, &L1Rect)) ||
		(L2Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Lrect, &L2Rect)) ||
		(L3Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Lrect, &L3Rect)) ||
		(L4Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Lrect, &L4Rect)))
	{
		(*_viEnemy)->getEnemyInfo()->Left = true;
	}
	else
	{
		(*_viEnemy)->getEnemyInfo()->Left = false;
		
	}
}

void EnemyManager::TopCollision(vector<Enemy*>::iterator viEnemy)
{
	RECT temp;
	BlockType T1Type = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->idx - 1) + (*_viEnemy)->getEnemyInfo()->idy]->blockType;
	BlockType T2Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()-> idx + (*_viEnemy)->getEnemyInfo()->idy]->blockType;
	BlockType T3Type = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->idx + 1) + (*_viEnemy)->getEnemyInfo()->idy]->blockType;
	BlockType T4Type = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->idx + 2) + (*_viEnemy)->getEnemyInfo()->idy]->blockType;
	RECT T1Rect = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->idx - 1) + (*_viEnemy)->getEnemyInfo()->idy]->rc;
	RECT T2Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->idx + (*_viEnemy)->getEnemyInfo()->idy]->rc;
	RECT T3Rect = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->idx + 1) + (*_viEnemy)->getEnemyInfo()->idy]->rc;
	RECT T4Rect = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->idx + 2) + (*_viEnemy)->getEnemyInfo()->idy]->rc;

	if ((T1Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Trect, &T1Rect)) ||
		(T2Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Trect, &T2Rect)) ||
		(T3Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Trect, &T3Rect)) ||
		(T4Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Trect, &T4Rect)))
	{
		(*_viEnemy)->getEnemyInfo()->Top = true;
	}
	else
	{
		(*_viEnemy)->getEnemyInfo()->Top = false;
		
	}
}

void EnemyManager::RightCollision(vector<Enemy*>::iterator viEnemy)
{
	RECT temp;
	BlockType R1Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid]->blockType;
	BlockType R2Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid + 1]->blockType;
	BlockType R3Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid + 2]->blockType;
	BlockType R4Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid + 3]->blockType;
	RECT R1Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid]->rc;
	RECT R2Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid + 1]->rc;
	RECT R3Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid + 2]->rc;
	RECT R4Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Rid + (*_viEnemy)->getEnemyInfo()->Tid + 3]->rc;

	if ((R1Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Rrect, &R1Rect)) ||
		(R2Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Rrect, &R2Rect)) ||
		(R3Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Rrect, &R3Rect)) ||
		(R4Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Rrect, &R4Rect)))
	{
		(*_viEnemy)->getEnemyInfo()->Right = true;
	}
	else
	{
		(*_viEnemy)->getEnemyInfo()->Right = false;
		
	}
}

void EnemyManager::BottomCollision(vector<Enemy*>::iterator viEnemy)
{
	RECT temp;
	BlockType B1Type = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->Lid - 1) + (*_viEnemy)->getEnemyInfo()->Bid]->blockType;
	BlockType B2Type = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()->Lid + (*_viEnemy)->getEnemyInfo()->	   Bid]->blockType;
	BlockType B3Type = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->Lid + 1) + (*_viEnemy)->getEnemyInfo()->Bid]->blockType;
	BlockType B4Type = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->Lid + 2) + (*_viEnemy)->getEnemyInfo()->Bid]->blockType;
	RECT B1Rect = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->Lid - 1) + (*_viEnemy)->getEnemyInfo()->Bid]->rc;
	RECT B2Rect = _Tile[MaxTile_Y * (*_viEnemy)->getEnemyInfo()-> Lid + (*_viEnemy)->getEnemyInfo()->	  Bid]->rc;
	RECT B3Rect = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->Lid + 1) + (*_viEnemy)->getEnemyInfo()->Bid]->rc;
	RECT B4Rect = _Tile[MaxTile_Y * ((*_viEnemy)->getEnemyInfo()->Lid + 2) + (*_viEnemy)->getEnemyInfo()->Bid]->rc;

	if ((B1Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Brect, &B1Rect)) ||
		(B2Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Brect, &B2Rect)) ||
		(B3Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Brect, &B3Rect)) ||
		(B4Type != BlockType::NONE && IntersectRect(&temp, &(*_viEnemy)->getEnemyInfo()->Brect, &B4Rect)))
	{
		(*_viEnemy)->getEnemyInfo()->Bottom = true;
	}
	else
	{
		(*_viEnemy)->getEnemyInfo()->Bottom = false;
		
	}
}

void EnemyManager::enemyRemove()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();)
	{
		if ((*_viEnemy)->getEnemyInfo()->HP < 1)
		{
			_vEnemy.erase(_viEnemy);
			break;
		}
		else
		{
			++_viEnemy;
		}
	}
}
