#pragma once
#include"gameNode.h"
#define TILESIZE 32
enum class Type
{
	SLIME,ZOMBIE,DEMONEYE,DEMON,BOSS
};
enum class Direction
{
	LEFT, RIGHT
};
enum class State
{
	MOVE,ATTACK,DIE
};
struct EnemyInfo
{
	Type type;
	int idx, idy;
	float x, y;
	float angle;
	float speed;
	float gravity;
	float damage;
	float HP;
	float Defense;
	RECT rc;
	image* enemyImage;
	Direction direction;
	State state;
	int FrameX, FrameY;
	float FrameCount;
	bool Jump;
	bool Top;
	bool Left;
	bool Right;
	bool Bottom;

	bool Hit;

	RECT Lrect;
	RECT Trect;
	RECT Rrect;
	RECT Brect;
	int Lid, Tid, Rid, Bid;
	float delay;
};
struct PlayerPos
{
	RECT rc;
	float x, y;
};
class Enemy:public gameNode
{
protected:
	EnemyInfo* _enemyInfo;
	PlayerPos* _playerPos;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void Move();
	virtual void Frame();
	//virtual void Knockback();
	virtual void Gravity();
	virtual void EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, image* enemyImage, Type type);
	virtual void EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, string enemyImage, Type type);
	virtual void Hit(bool hit, float damage);
	virtual void delayReset() { _enemyInfo->delay = 0; }
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }
	virtual void setPlayerPos(RECT rc, float x, float y) { _playerPos->rc = rc;_playerPos->x = x;_playerPos->y = y; }
};

