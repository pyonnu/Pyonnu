#pragma once
#include"gameNode.h"
class Lobby:public gameNode
{
private:
	image* _lobbyImage;
	
public:
	Lobby() {};
	~Lobby() {};

	HRESULT init();
	void release();
	void update();
	void render();
};

