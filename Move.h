#pragma once
#include"gameNode.h"
class Move:public gameNode
{
private:
	float _Acceleration;
	float _MaxSpeed;
	float _Speed;
	float _Deceleration;
	float _Angle;
	bool _Accelerating;
public:
	HRESULT init();
	void release();
	void update();

	void Acceleration(float speed,float maxSpeed,float angle);
	void Deceleration(float speed,float maxSpeed,float angle);
};

