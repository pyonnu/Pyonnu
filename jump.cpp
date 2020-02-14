#include "stdafx.h"
#include "Jump.h"

Jump::Jump()
{
}

Jump::~Jump()
{
}

HRESULT Jump::init()
{
	_isJumping = _jumpPower = _gravity = 0;

	return S_OK;
}

void Jump::release()
{
}

void Jump::update()
{
	if (!_isJumping) return;

	*_y -= _jumpPower;
	_jumpPower -= _gravity;

	if (_startY < *_y)
	{
		_isJumping = false;
		*_y = _startY;
	}
}

void Jump::jumping(float* x, float* y, float jumpPower, float gravity)
{
	//점프중이면 리턴 이말은 점프중이면 실행하지마렁
	if (_isJumping) return;

	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	//call by value
	//call by reference

	_gravity = gravity;
	_jumpPower = jumpPower;
}
