#pragma once
#include "gameNode.h"

class Jump:public gameNode
{
private:
	float _jumpPower;
	float _gravity;

	float* _y;

	float _startY;
	bool _isJumping;

public:
	Jump();
	~Jump();

	HRESULT init(float* y);
	void release();
	void update();
	void update(bool down,bool up);
	void power0() { _jumpPower = 0; }
	void jumping(float* x, float* y, float jumpPower, float gravity);
};

