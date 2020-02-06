#pragma once
#include"gameNode.h"

class Lobby :public gameNode
{
private:
	image* _lobbyImage;		//로비의 이미지를 담을 image클래스
	RECT _button[4];
public:
	Lobby() {};
	~Lobby() {};

	HRESULT init();
	void release();
	void update();
	void render();

};
