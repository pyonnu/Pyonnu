#pragma once
#include"Enemy.h"
enum class Phase
{
	PHASE1,PHASE2
};
class EyeOfCthulhu:public Enemy
{
private:
	Phase phase;
public:
	void EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, image* enemyImage);
	void EnemyCreate(float x, float y, float speed, float HP, float Defense, float damage, string enemyImage);
	void Move();
	void Frame();
};

