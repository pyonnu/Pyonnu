#pragma once
#include"gameNode.h"

class Lobby :public gameNode
{
private:
	image* _lobbyImage;		//�κ��� �̹����� ���� imageŬ����
	RECT _button[4];
public:
	Lobby() {};
	~Lobby() {};

	HRESULT init();
	void release();
	void update();
	void render();

};
