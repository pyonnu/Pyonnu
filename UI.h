#pragma once
#include"gameNode.h"
#include"Inventory.h"
class UI:public gameNode
{
private:
	Inventory* _inventory;
	float _HP;
	float _MaxHP;
	float _Defense;
	float _Damage;
	float _ToolsPower;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setplayerInfo(float MaxHP, float hp, float defense) { _MaxHP = MaxHP;_HP = hp; _Defense = defense; }
	//void setWeaponInfo(float damage, float toolspower);
	
};

