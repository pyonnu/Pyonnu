#pragma once
#include"gameNode.h"
#include"Lobby.h"
#include"MapTool.h"
class Scene:public gameNode
{
private:
	Lobby* _lobby;
	MapTool* _mapTool;
	
public:
	Scene() {};
	~Scene() {};

	HRESULT init();
	void release();
	void update();
	void render();
};

