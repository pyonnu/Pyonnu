#pragma once
#include"gameNode.h"
#include"Item.h"
#include"jump.h"
#include"Move.h"
#include"Attack.h"
class EnemyManager;
enum class PlayerDirection
{
	LEFT,RIGHT
};
enum class PlayerState
{
	IDLE,MOVE,JUMP,ATTACK
};
struct PlayerInfo
{
	int idx, idy;
	float x, y;
	RECT rect;
	RECT attackRect;
	float speed;
	float damage;
	float Defense;
	PlayerState state;
	PlayerDirection direction;
	int FrameX;
	int FrameY;
	float FrameCount;
	image* Head;
	image* Body;
	image* Legs;
	image* HeadArmor;
	image* BodyArmor;
	image* LegsArmor;
};
class Player :public gameNode
{
private:
	EnemyManager* _enemyManager;
	PlayerInfo _playerInfo;
	Move* _move;
	Jump* _jump;
	Attack* _attack;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemyManagerLink(EnemyManager* Link) { _enemyManager = Link; }

};
