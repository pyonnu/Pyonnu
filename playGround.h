#pragma once
#include "gameNode.h"
#include"Scene.h"

class playGround : public gameNode
{
private:
	Scene* _scene;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();	//�׸��� ���� �Լ�
	
	void imageAdd();
};

