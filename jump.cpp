#include "stdafx.h"
#include "Jump.h"

Jump::Jump()
{
}

Jump::~Jump()
{
}

HRESULT Jump::init(float* y)
{
	_isJumping = _jumpPower = _gravity = 0;
	_y = y;
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

	/*if (_starty < *_y)
	{
		_isjumping = false;
		*_y = _starty;
	}*/
}

void Jump::update(bool down,bool up)
{

	if (!_isJumping) return ;

	if (up)_jumpPower = 0;
	if (_jumpPower <= -20)_jumpPower = -20;
	*_y -= _jumpPower;
	_jumpPower -= _gravity;

	if (_startY <= *_y)_isJumping = false;
}

void Jump::jumping(float* x, float* y, float jumpPower, float gravity)
{
	//점프중이면 리턴 이말은 점프중이면 실행하지마렁
	if (_isJumping) return;

	_isJumping = true;

	_y = y;

	_startY = *y;
	//call by value
	//call by reference

	_gravity = gravity;
	_jumpPower = jumpPower;
}
