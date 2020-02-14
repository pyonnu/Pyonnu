#pragma once
#include "gameNode.h"

class Jump:public gameNode
{
private:
	float _jumpPower;
	float _gravity;

	float* _x;
	float* _y;

	float _startX, _startY;

	bool _isJumping;

public:
	Jump();
	~Jump();

	HRESULT init();
	void release();
	void update();

	void jumping(float* x, float* y, float jumpPower, float gravity);
};

