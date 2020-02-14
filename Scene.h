#pragma once
#include"gameNode.h"
#include"Lobby.h"
#include"MapTool.h"
#include"World.h"
class Scene:public gameNode
{
private:
	Lobby* _lobby;
	MapTool* _mapTool;
	World* _world;
public:
	Scene() {};
	~Scene() {};

	HRESULT init();
	void release();
	void update();
	void render();
};

