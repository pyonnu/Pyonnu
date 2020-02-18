#pragma once
#include"gameNode.h"
#include"Item.h"
#include"jump.h"
#include"Move.h"
#include"Attack.h"
#include"Tile.h"
class EnemyManager;
enum class PlayerDirection
{
	LEFT,RIGHT
};
enum class PlayerHeadState
{
	IDLE,MOVE,JUMP,ATTACK
};
enum class PlayerBodyState
{
	IDLE, MOVE, JUMP, ATTACK
};
enum class PlayerLegsState
{
	IDLE, MOVE, JUMP, ATTACK
};
struct PlayerInfo
{
	POINT index;
	POINT L1Index;
	POINT L2Index;
	POINT L3Index;
	POINT U1Index;
	POINT U2Index;
	POINT R1Index;
	POINT R2Index;
	POINT R3Index;
	POINT D1Index;
	POINT D2Index;
	float x, y;
	RECT rect;
	RECT lRect;
	RECT rRect;
	RECT uRect;
	RECT dRect;

	RECT attackRect;
	float speed;
	float damage;
	float Defense;
	PlayerHeadState HeadState;
	PlayerBodyState BodyState;
	PlayerLegsState LegsState;
	PlayerDirection direction;
	int FrameX;
	int HeadFrameY;
	int BodyFrameY;
	int LegsFrameY;
	float FrameCount;
	image* Head;
	image* Body;
	image* Legs;
	image* HeadArmor;
	image* BodyArmor;
	image* LegsArmor;

	bool Up;
	bool Left;
	bool Right;
	bool Down;

};
class Player :public gameNode
{
private:
	EnemyManager* _enemyManager;
	Item* _item;
	PlayerInfo _playerInfo;
	Move* _move;
	Jump* _jump;
	Attack* _attack;

	tagTile _Tile[MaxTile_X][MaxTile_Y];
	
	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viTile;

	map<POINT*, tagTile*> _mTile;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void PlayerIndexUpdate();
	void Action();
	void Frame();
	void BlockCollision();
	void LeftBlockCollision();
	void RightBlockCollision();
	void UpBlockCollision();
	void DownBlockCollision();
	void EnemyManagerLink(EnemyManager* Link) { _enemyManager = Link; }

	//void setTile(tagTile* tile) { _Tile = tile; }
	void setVTile(vector<tagTile*> vtile) { _vTile = vtile; }
	void setViTile(vector<tagTile*>::iterator viTile) { _viTile = viTile; }

	//void setTile(tagTile tile) { _Tile[MaxTile_X][MaxTile_Y] = tile; }

	PlayerInfo getPlayerInfo() { return _playerInfo; }
};
