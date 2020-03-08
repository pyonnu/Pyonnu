#pragma once
#include"Enemy.h"
class Slime:public Enemy
{
private:
	int delay = 0;
	void Move();
	void Frame();
	void Gravity();
};

