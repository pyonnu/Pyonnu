#pragma once
#include "gameNode.h"
#include"Scene.h"
#define MaxItem 67
class playGround : public gameNode
{
private:
	Scene* _scene;
public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render();	//그리기 전용 함수
	
	void imageAdd();
	void itemAdd();
};

