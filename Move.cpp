#include "stdafx.h"
#include "Move.h"

HRESULT Move::init()
{
	_MaxSpeed = _Acceleration = _Deceleration =_Angle =_Speed = 0;
	_Accelerating = false;
	return S_OK;
}

void Move::release()
{
}

void Move::update()
{
}


void Move::Acceleration(float speed, float maxSpeed, float angle)
{
	_MaxSpeed = maxSpeed;
	_Acceleration = speed;
	_Angle = angle;
	_Accelerating = true;
}

void Move::Deceleration(float speed, float maxSpeed, float angle)
{
	if (!_Accelerating)return;
}