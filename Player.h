#pragma once
#include"gameNode.h"
#include"jump.h"
#include"Move.h"
#include"Attack.h"
#include"Tile.h"
class EnemyManager;
enum class PlayerDirection
{
	LEFT, RIGHT
};
enum class PlayerHeadState
{
	IDLE, MOVE, JUMP, ATTACK
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
	float x, y;
	RECT rect;
	RECT Lrect;
	RECT Trect;
	RECT Rrect;
	RECT Brect;
	RECT attackRect;
	float attackX;
	float attackY;
	float angle;
	float speed;
	float damage;
	float Defense;
	float Health;
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

	bool Attack;
	bool jump;
};
class Player :public gameNode
{
private:
	EnemyManager* _enemyManager;
	PlayerInfo _playerInfo;
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;
	Move* _move;
	Jump* _jump;
	Attack* _attack;



	float _gravity;

	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viTile;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void PlayerInfoUpdate();
	void Action();
	void Frame();
	void BlockCollision();
	void ItemCollision();
	void TileDestroyCreate(int mouse);
	void InventoryItemAdd(vector<Item*>::iterator viItem);
	void LeftBlockCollision();
	void RightBlockCollision();
	void UpBlockCollision();
	void DownBlockCollision();
	void EnemyManagerLink(EnemyManager* Link) { _enemyManager = Link; }

	void setVTile(vector<tagTile*> vtile) { _vTile = vtile; }
	void setViTile(vector<tagTile*>::iterator viTile) { _viTile = viTile; }

	PlayerInfo getPlayerInfo() { return _playerInfo; }
	int getStartX();
	int getEndX();
	int getStartY();
	int getEndY();
};
