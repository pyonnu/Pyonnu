#include "stdafx.h"
#include "Player.h"
#include"EnemyManager.h"
HRESULT Player::init()
{
	_jump = new Jump;
	_move = new Move;
	_attack = new Attack;
	_jump->init();
	_move->init();
	_attack->init();
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	_enemyManager = new EnemyManager;
	_playerInfo.state = PlayerState::IDLE;
	_playerInfo.direction = PlayerDirection::LEFT;

	_playerInfo.FrameCount = 0;
	_playerInfo.FrameX = 0;
	_playerInfo.FrameY = 0;

	_playerInfo.rect = RectMakeCenter(WINSIZEX/2, WINSIZEX/2, 40, 90);
	_playerInfo.Head = IMAGEMANAGER->findImage("Player_Head");
	_playerInfo.Body = IMAGEMANAGER->findImage("Player_Body");
	_playerInfo.Legs = IMAGEMANAGER->findImage("Player_Legs");

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
	Rectangle(CAMERAMANAGER->getCameraDC(), _playerInfo.rect);
	_playerInfo.Head->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left,_playerInfo.rect.top,1,0);
	_playerInfo.Body->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left, _playerInfo.rect.top+2,1,0);
	_playerInfo.Legs->frameRender(CAMERAMANAGER->getCameraDC(), _playerInfo.rect.left, _playerInfo.rect.top+2,1,0);
}
