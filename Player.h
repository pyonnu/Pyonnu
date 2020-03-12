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
enum class PlayerState
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
	float attackSpeed;
	float damage;
	float Defense;
	float Health;
	float MaxHealth;
	PlayerState HeadState;
	PlayerState BodyState;
	PlayerState LegsState;
	PlayerDirection direction;
	PlayerDirection currentDirection;
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
	image* attackImage;

	bool Up;
	bool Left;
	bool Right;
	bool Down;

	bool Attack;
	bool AttackIng;
	bool jump;
	bool hit;
	float delay;
	float timer;

	bool WORKBENCH;
	bool ANVIL;
	bool FURNACE;
	bool DEMONALTER;

	bool crash;
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
	void Attack(int mouse);
	void Frame();
	void BlockCollision();
	void ItemCollision();
	void TileDestroyCreate(int mouse);
	void TileDestroy(int mouse);
	void InventoryItemAdd(vector<Item*>::iterator viItem);
	void LeftBlockCollision();
	void RightBlockCollision();
	void UpBlockCollision();
	void DownBlockCollision();
	void EnemyManagerLink(EnemyManager* Link) { _enemyManager = Link; }

	void setVTile(vector<tagTile*> vtile) { _vTile = vtile; }
	void setViTile(vector<tagTile*>::iterator viTile) { _viTile = viTile; }
	
	void Hit(float damage);
	void delaytReset() { _playerInfo.delay = 0; }

	PlayerInfo getPlayerInfo() { return _playerInfo; }
	RECT getRect() { return _playerInfo.rect; }
	RECT getAttackRect() { return _playerInfo.attackRect; }
	int getStartX();
	int getEndX();
	int getStartY();
	int getEndY();

	void Save();
	void Load();

	bool getWorkbench() { return _playerInfo.WORKBENCH; }
	bool getFurnace() { return _playerInfo.FURNACE; }
	bool getAnvil() { return _playerInfo.ANVIL; }
	bool getDemonAlter() { return _playerInfo.DEMONALTER; }

	float getDelay() { return _playerInfo.delay; }
};
